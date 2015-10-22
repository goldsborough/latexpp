#ifndef LATEX_HPP
#define LATEX_HPP

#include <memory>
#include <stdexcept>
#include <string>
#include <v8.h>

class Latex
{
public:
	
	struct ParseException : public std::runtime_error
	{
		ParseException(const std::string& what)
		: std::runtime_error(what)
		{ }
	};

	Latex();
	
	Latex(const Latex& other);
	
	Latex(Latex&& other) noexcept;
	
	Latex& operator=(Latex other);
	
	virtual void swap(Latex& other) noexcept;
	
	friend void swap(Latex& first, Latex& second) noexcept;
	
	virtual ~Latex();
	
	
	virtual std::string render(const std::string& latex) const;
	
	
protected:
	
	struct Allocator : public v8::ArrayBuffer::Allocator
	{
		virtual void* Allocate(size_t length) override;
		
		virtual void* AllocateUninitialized(size_t length) override;
		
		virtual void Free(void* data, size_t) override;
	};
	
	virtual v8::Isolate* _new_isolate() const;
	
	virtual void _initialize_v8() const;
	
	virtual void _load_katex(const v8::Local<v8::Context>& context) const;
	
	virtual v8::Local<v8::Value> _run(const std::string& source,
							  	      const v8::Local<v8::Context>& context) const;
	
	virtual std::string _escape(std::string source) const;
	
	
	std::unique_ptr<v8::Platform> _platform;
	
	mutable Allocator _allocator;

	v8::Isolate* _isolate;
	
	v8::UniquePersistent<v8::Context> _persistent_context;
};

#endif /* LATEX_HPP */