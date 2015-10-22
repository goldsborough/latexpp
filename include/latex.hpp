/********************************************************//*!
*
*	@file latex.hpp
*
*	@author Peter Goldsborough.
*
************************************************************/

#ifndef LATEX_HPP
#define LATEX_HPP

#include <memory>
#include <stdexcept>
#include <string>
#include <v8.h>

class wkhtmltoimage_converter;
class wkhtmltoimage_global_settings;

class Latex
{
public:
	
	/***********************************************************************//*!
	*
	*	@brief The available image formats.
	*
	***************************************************************************/

	enum class ImageFormat { PNG, SVG, JPG };
	
	/***********************************************************************//*!
	*
	*	@brief The types of warning behavior.
	*
	*	@details Use WarningBehavior::Strict to escalate any warnings
	*		     generated during image conversion as exceptions, i.e.
	*			 for them to be thrown as a Latex::ConversionException.
	*
	***************************************************************************/
	
	enum class WarningBehavior { Strict, Ignore, Log };

	/***********************************************************************//*!
	*
	*	@brief An exception thrown by the LaTeX parsing mechanism.
	*
	***************************************************************************/
	
	struct ParseException : public std::runtime_error
	{
		ParseException(const std::string& what)
		: std::runtime_error(what)
		{ }
	};
	
	/***********************************************************************//*!
	*
	*	@brief An exception thrown during the latex-to-image conversion.
	*
	***************************************************************************/
	
	struct ConversionException : public std::runtime_error
	{
		ConversionException(const std::string& what)
		: std::runtime_error(what)
		{ }
	};
	
	/***********************************************************************//*!
	*
	*	@brief An exception thrown during file-manipulation.
	*
	***************************************************************************/
	
	struct FileException : public std::runtime_error
	{
		FileException(const std::string& what)
		: std::runtime_error(what)
		{ }
	};

	/***********************************************************************//*!
	*
	*	@brief Constructs a Latex instance.
	*
	*	@details This constructor differs from the other in that it uses
	*			 the KaTeX stylesheet by default. You will very rarely
	*			 not want to use this one.
	*
	*	@param behavior The warning behavior to use.
	*
	*	@see WarningBehavior
	*
	***************************************************************************/

	Latex(WarningBehavior behavior = WarningBehavior::Log);
	
	/***********************************************************************//*!
	*
	*	@brief Constructs a Latex instance.
	*
	*	@param stylesheet The file-path of the CSS stylesheet to use
	*				      for styling the KaTeX HTML output.
	*
	*	@param behavior The warning behavior to use.
	*
	*	@see WarningBehavior
	*
	***************************************************************************/
	
	Latex(const std::string& stylesheet_path,
		  WarningBehavior behavior = WarningBehavior::Log);
	
	Latex(const Latex& other);
	
	Latex(Latex&& other) noexcept;
	
	Latex& operator=(Latex other);
	
	virtual void swap(Latex& other) noexcept;
	
	friend void swap(Latex& first, Latex& second) noexcept;
	
	virtual ~Latex();
	
	
	virtual std::string html(const std::string& latex) const;
	
	virtual std::string complete_html(const std::string& latex) const;
	
	
	virtual void image(const std::string& latex,
					   const std::string& filename,
					   ImageFormat format) const;
	
	virtual void png(const std::string& latex,
					 const std::string& filename) const;
	
	virtual void jpg(const std::string& latex,
					 const std::string& filename) const;
	
	virtual void svg(const std::string& latex,
					 const std::string& filename) const;
	
	
	virtual void add_css(const std::string& css);
	
	virtual const std::string& additional_css() const;
	
	virtual void clear_additional_css();
	
	
	virtual const std::string& stylesheet() const;
	
	virtual void stylesheet(const std::string& stylesheet);
	
	
	virtual	const WarningBehavior& exception_behavior() const;
	
	virtual void exception_behavior(WarningBehavior behavior);
	
	
protected:
	
	static struct V8
	{
		V8();
		
		~V8();
	
		std::unique_ptr<v8::Platform> platform;
		
	} v8;
	
	struct Allocator : public v8::ArrayBuffer::Allocator
	{
		virtual void* Allocate(size_t length) override;
		
		virtual void* AllocateUninitialized(size_t length) override;
		
		virtual void Free(void* data, size_t) override;
	};
	
	virtual std::string _read_stylesheet(const std::string& path) const;
	
	virtual v8::Isolate* _new_isolate() const;
	
	virtual void _load_katex(const v8::Local<v8::Context>& context) const;
	
	virtual v8::Local<v8::Value> _run(const std::string& source,
							  	      const v8::Local<v8::Context>& context) const;
	
	virtual std::string _escape(std::string source) const;
	
	virtual wkhtmltoimage_converter*
	_new_converter(const std::string& filename, ImageFormat format) const;
	
	virtual wkhtmltoimage_global_settings*
	_new_converter_settings(const std::string& filename,
							ImageFormat format) const;
	
	friend void _throw(wkhtmltoimage_converter* converter,
					   const char* message);
	
	friend void _log(wkhtmltoimage_converter* converter,
					 const char* message);
	
	mutable Allocator _allocator;

	v8::Isolate* _isolate;
	
	v8::UniquePersistent<v8::Context> _persistent_context;
	
	std::string _stylesheet_path;
	
	std::string _stylesheet;
	
	std::string _additional_css;
	
	WarningBehavior _warning_behaviour;
};

#endif /* LATEX_HPP */