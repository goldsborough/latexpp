#include "latex.hpp"

#include <cstdlib>
#include <fstream>
#include <libplatform/libplatform.h>

Latex::Latex()
: _platform(v8::platform::CreateDefaultPlatform())
{
	_initialize_v8();
	
	_isolate = _new_isolate();
	
	v8::HandleScope handle_scope(_isolate);
	
	v8::Isolate::Scope isolate_scope(_isolate);
	
	auto context = v8::Context::New(_isolate);
	
	v8::Context::Scope context_scope(context);
	
	_load_katex(context);
	
	_persistent_context = v8::UniquePersistent<v8::Context>(_isolate, context);
}

Latex::Latex(const Latex& other)
: _platform(v8::platform::CreateDefaultPlatform())
, _allocator(other._allocator)
{
	_initialize_v8();
}

Latex::Latex(Latex&& other) noexcept
: Latex()
{
	swap(other);
}

Latex& Latex::operator=(Latex other)
{
	swap(other);
	
	return *this;
}

void Latex::swap(Latex &other) noexcept
{
	// Enable ADL
	using std::swap;
	
	swap(_platform, other._platform);
	
	swap(_allocator, other._allocator);
}

void swap(Latex& first, Latex& second) noexcept
{
	first.swap(second);
}

Latex::~Latex()
{
	v8::V8::Dispose();
	
	v8::V8::ShutdownPlatform();
}

std::string Latex::render(const std::string& latex) const
{
	v8::Isolate::Scope isolate_scope(_isolate);
	
	// Stack-allocated handle-scope (takes care of handles such
	// that object are garbage-collected after the scope ends)
	v8::HandleScope handle_scope(_isolate);
	
	// Get a local context handle from the persistent handle.
	auto context = v8::Local<v8::Context>::New(_isolate, _persistent_context);
	
	v8::Context::Scope context_scope(context);
	
	auto source = "katex.renderToString('" + _escape(latex) + "');";
	
	auto html = _run(source, context);
	
	return *static_cast<v8::String::Utf8Value>(html);
}

void Latex::_initialize_v8() const
{
	v8::V8::InitializeICU();
	
	v8::V8::InitializePlatform(_platform.get());
	
	v8::V8::Initialize();
}

void Latex::_load_katex(const v8::Local<v8::Context>& context) const
{
	std::ifstream file("../../katex/katex.min.js");
	
	std::string source;
	std::string input;
	
	while (std::getline(file, input))
	{
		source += input + " ";
	}
	
	_run(source, context);
}

v8::Local<v8::Value> Latex::_run(const std::string& source,
								 const v8::Local<v8::Context>& context) const
{
	v8::EscapableHandleScope handle_scope(_isolate);
	
	auto unchecked = v8::String::NewFromUtf8(_isolate,
											 source.c_str(),
											 v8::NewStringType::kNormal);
	
	auto checked = unchecked.ToLocalChecked();

	// Compile the source code.
	auto script = v8::Script::Compile(context, checked).ToLocalChecked();
	
	v8::TryCatch try_catch(_isolate);
	
	auto result = script->Run(context);
	
	if (result.IsEmpty())
	{
		auto exception = try_catch.Exception();
		
		std::string what = *static_cast<v8::String::Utf8Value>(exception);
		
		// Remove the 'ParseError' (redundant)
		throw ParseException(what.substr(12));
	}
	
	// Allows us to return local-scope objects to the outside scope
	return handle_scope.Escape(result.ToLocalChecked());
}

std::string Latex::_escape(std::string source) const
{
	for (auto i = source.begin(); i != source.end(); ++i)
	{
		if (*i == '\\')
		{
			i = source.insert(i, '\\');
			
			++i;
		}
	}
	
	return source;
}

v8::Isolate* Latex::_new_isolate() const
{
	v8::Isolate::CreateParams parameters;
	
	parameters.array_buffer_allocator = &_allocator;
	
	// Isolated JavaScript Virtual Environment
	return v8::Isolate::New(parameters);
}

void* Latex::Allocator::Allocate(size_t length)
{
	auto data = AllocateUninitialized(length);
	
	return data ? memset(data, 0, length) : data;
}

void Latex::Allocator::Free(void *data, size_t)
{
	free(data);
}

void* Latex::Allocator::AllocateUninitialized(size_t length)
{
	return malloc(length);
}