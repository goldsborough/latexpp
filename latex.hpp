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
	
	/*! The path to the KaTeX directory. */
	static std::string _katex_path;
	
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
	*	@brief An exception thrown during the LaTeX-to-image conversion.
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
	*	@brief An exception signifying that Latex cannot function correctly.
	*
    *   @details More specifically, this exception will be thrown if essential
    *			 dependency-paths (for KaTeX) were not found on start-up.
    *
	***************************************************************************/
	
	struct ExistentialException : public std::runtime_error
	{
		ExistentialException(const std::string& what)
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
	
	Latex(const std::string& stylesheet,
		  WarningBehavior behavior = WarningBehavior::Log);
	
	/***********************************************************************//*!
	*
	*	@brief Copy-constructs a Latex instance.
	*
	*	@param other Another Latex instance.
	*
	***************************************************************************/
	
	Latex(const Latex& other);
	
	/***********************************************************************//*!
	*
	*	@brief Move-constructs a Latex instance.
	*
	*	@param other Another Latex instance.
	*
	***************************************************************************/
	
	Latex(Latex&& other) noexcept;
	
	/***********************************************************************//*!
	*
	*	@brief Assigns another Latex instance to this one.
	*
	*	@param other Another Latex instance.
	*
	***************************************************************************/
	
	Latex& operator=(Latex other);
	
	/***********************************************************************//*!
	*
	*	@brief Swaps data with another Latex instance.
	*
	*	@param other Another Latex instance.
	*
	***************************************************************************/
	
	virtual void swap(Latex& other) noexcept;
	
	/***********************************************************************//*!
	*
	*	@brief Swaps the data of two Latex instances.
	*
	*	@param first The first Latex instance.
	*
	*	@param second The second Latex instance.
	*
	***************************************************************************/
	
	friend void swap(Latex& first, Latex& second) noexcept;
	
	/***********************************************************************//*!
	*
	*	@brief Destructs the Latex instance.
	*
	***************************************************************************/
	
	virtual ~Latex();
	
	/***********************************************************************//*!
	*
	*	@brief Converts a LaTeX snippet to an HTML snippet.
	*
	*	@details Note that this method does not return a complete, valid
	*			 html document. It returns a span containing the KaTeX-
	*			 processed html, ready for embedding in a HTML-document
	*			 including the KaTeX stylesheet. If you need a complete
	*			 document (i.e. one that would really render as a file
	*			 in a browser), call to_complete_html(); Be sure to
	*			 escape backlashes in the argument of this function.
	*
	*	@param latex The LaTeX snippet to render.
	*
	*	@return An HTML *snippet*.
	*
	*	@see to_complete_html()
	*
	*	@throws ParseException If the parsing of the latex snippet failed.
	*
	***************************************************************************/
	
	virtual std::string to_html(const std::string& latex) const;
	
	/***********************************************************************//*!
	*
	*	@brief Converts a LaTeX snippet to a complete, valid HTML document.
	*
	*	@param latex The LaTeX snippet to render.
	*
	*	@return	A complete and valid HTML web-page.
	*
	*	@see to_complete_html()
	*
	*	@throws ParseException If the parsing of the latex snippet failed.
	*
	***************************************************************************/
	
	virtual std::string to_complete_html(const std::string& latex) const;
	
	/***********************************************************************//*!
	*
	*	@brief Converts a LaTeX snippet to an image.
	*
	*	@param latex The LaTeX snippet to render.
	*
	*	@param filepath The file-path at which to store the output image.
	*
	*	@param format Which image format to output as.
	*
	*	@return	An image of the format specified by the format argument.
	*
	*	@throws ParseException If the parsing of the latex snippet failed.
	*
	*	@throws ConversionException If the conversion of the latex snippet
	*							    to an image failed.
	*
    *	@throws FileException If a temporary helper file could not be opened.
    *
	***************************************************************************/
	
	virtual void to_image(const std::string& latex,
					   const std::string& filepath,
					   ImageFormat format) const;
	
	/***********************************************************************//*!
	*
	*	@brief Converts a LaTeX snippet to a PNG image.
	*
	*	@param latex The LaTeX snippet to render.
	*
	*	@param filepath The file-path at which to store the output image.
	*
	*	@see to_image()
	*
	*	@throws ParseException If the parsing of the latex snippet failed.
	*
	*	@throws ConversionException If the conversion of the latex snippet
	*							    to an image failed.
	*
	*	@throws FileException If a temporary helper file could not be opened.
	*
	***************************************************************************/
	
	virtual void to_png(const std::string& latex,
					 const std::string& filepath) const;

	/***********************************************************************//*!
	*
	*	@brief Converts a LaTeX snippet to a JPG image.
	*
	*	@param latex The LaTeX snippet to render.
	*
	*	@param filepath The file-path at which to store the output image.
	*
	*	@see to_image()
	*
	*	@throws ParseException If the parsing of the latex snippet failed.
	*
	*	@throws ConversionException If the conversion of the latex snippet
	*							    to an image failed.
	*
	*	@throws FileException If a temporary helper file could not be opened.
	*
	***************************************************************************/
	
	virtual void to_jpg(const std::string& latex,
					 const std::string& filepath) const;
	
	/***********************************************************************//*!
	*
	*	@brief Converts a LaTeX snippet to an SVG image.
	*
	*	@param latex The LaTeX snippet to render.
	*
	*	@param filepath The file-path at which to store the output image.
	*
	*	@see to_image()
	*
	*	@throws ParseException If the parsing of the latex snippet failed.
	*
	*	@throws ConversionException If the conversion of the latex snippet
	*							    to an image failed.
	*
	*	@throws FileException If a temporary helper file could not be opened.
	*
	***************************************************************************/
	
	virtual void to_svg(const std::string& latex,
					 const std::string& filepath) const;
	
	/***********************************************************************//*!
	*
	*	@brief Adds additional CSS to the base-stylesheet.
	*
	*	@details The idea is that you have one base-stylesheet, most likely
	*			 the one provided by KaTeX, but you can cascade (smaller)
	*			 bits of CSS to, for example, only change the font-color.
    *		     Use the `.latex` class for the CSS.
	*
	*	@example `add_css(".late { color: red; }")`
	*
	*	@param css The additioanal CSS to add to the base-stylesheet.
	*
	*	@see additional_css()
	*
	*	@see clear_additional_css()
	*
	***************************************************************************/
	
	virtual void add_css(const std::string& css);
	
	/***********************************************************************//*!
	*
	*	@brief Returns the additional CSS added via add_css().
	*
	***************************************************************************/
	
	virtual const std::string& additional_css() const;
	
	/***********************************************************************//*!
	*
	*	@brief Clears the additional CSS added via add_css().
	*
	***************************************************************************/
	
	virtual void clear_additional_css();

	/***********************************************************************//*!
	*
	*	@brief Returns the path to the stylesheet being used.
	*
	***************************************************************************/
	
	virtual const std::string& stylesheet() const;

	/***********************************************************************//*!
	*
	*	@brief Sets the base-stylesheet from a given path.
	*
	*	@details Note that you will seldom want to change the base-stylesheet.
	*			 If you want to add some additional bit of CSS, use add_css().
	*
	*	@param path A path to a CSS stylesheet to load.
	*
	***************************************************************************/
	
	virtual void stylesheet(const std::string& path);
	
	/***********************************************************************//*!
	*
	*	@brief Returns the currently in-place warning behavior.
	*
	*	@return The warning behavior, as a member of the WarningBehavior enum.
	*
	***************************************************************************/
	
	virtual	const WarningBehavior& warning_behavior() const;

	/***********************************************************************//*!
	*
	*	@brief Sets the warning behavior.
	*
	*	@param behavior The new warning behavior, a member of
	*		   			the WarningBehavior enum.
	*
	***************************************************************************/
	
	virtual void warning_behavior(WarningBehavior behavior);
	
	
protected:

	/***********************************************************************//*!
	*
	*	@brief Attempts to find the KaTeX directory.
	*
    *   @details Starts at the currentd directory and goes up a maximum of two.
    *
	*	@throws ExistentialException if the KaTeX directory was not found.
	*
	***************************************************************************/
	
	static std::string _find_katex_path();
	
	/***********************************************************************//*!
	*
	*	@brief A static wrapper singleton around the V8 engine.
	*
	*	@details The point of this is to, on the one hand, ensure that only
	*			 one v8 platform is used for all instances of the Latex,
	*			 class and, on the other hand, to enable easy initialization
	*			 and deinitialization of the V8 engine. This follows the RAII
	*			 principle
	*
	***************************************************************************/
	
	static struct V8
	{
	
		/*******************************************************************//*!
		*
		*	@brief Initializes the V8 engine.
		*
		***********************************************************************/
	
		V8();

		/*******************************************************************//*!
		*
		*	@brief De-initializes the V8 engine.
		*
		***********************************************************************/
		
		~V8();
	
		/* The static and unique platform for the V8 engine. */
		std::unique_ptr<v8::Platform> platform;
		
	} v8;
	
	/***********************************************************************//*!
	*
	*	@brief An ArrayBuffer allocator subclass required by the V8 engine.
	*
	***************************************************************************/
	
	struct Allocator : public v8::ArrayBuffer::Allocator
	{
		virtual void* Allocate(size_t length) override;
		
		virtual void* AllocateUninitialized(size_t length) override;
		
		virtual void Free(void* data, size_t) override;
	};

	
	/***********************************************************************//*!
	*
	*	@brief Creates and initializes a new v8::Isolate.
	*
	*	@details Deals with setting the Allocator instance in the
	*			 isolate's parameters.
	*
	*	@return A __pointer__ to a v8::Isolate.
	*
	***************************************************************************/

	virtual v8::Isolate* _new_isolate() const;
	
	/***********************************************************************//*!
	*
	*	@brief Loads the KaTeX JavaScript library.
	*
	*	@details The KaTeX library is loaded and executed in the current
	*			 V8 context, such that subsequent code executed in that
	*			 environment can access the KaTeX library.
	*
	*	@param	context A V8 context object.
	*
	***************************************************************************/
	
	virtual void _load_katex(const v8::Local<v8::Context>& context) const;
	
	/***********************************************************************//*!
	*
	*	@brief Compiles and executes JavaScript code via the V8 engine.
	*
	*	@param source The JavaScript source-code to execute.
	*
	*	@param context The context in which to compile and execute the code.
	*
	*	@return Any return value of the execution.
	*
	*	@throws ParseException If there was an exception in the JS environment,
	*						   which can only stem from a parse-exception.
	*
	***************************************************************************/
	
	virtual v8::Local<v8::Value> _run(const std::string& source,
							  	      const v8::Local<v8::Context>& context) const;
	
	/***********************************************************************//*!
	*
	*	@brief Escapes the backslashes in LaTeX source for rendering.
	*
	*	@details The problem is that even though you may escape backslashes
	*			 in the string you pass to the Latex instance, those
	*			 backlashes then have to again be escaped for the JavaScript
	*			 source (as they are simply backslashes for the JS
	*			 environment otherwise, which initiate escape sequences).
	*
	*	@return The escaped LaTeX string.
	*
	***************************************************************************/
	
	virtual std::string _escape(std::string source) const;
	
	/***********************************************************************//*!
	*
	*	@brief Requests, initializes and returns a wkhtmltoimage converter.
	*
	*	@param filepath The output file at which to store the converted file.
	*
	*	@param format The image-format to convert to.
	*
	*	@return A pointer to a wkhtmltoimage_converter instance.
	*
	***************************************************************************/
	
	virtual wkhtmltoimage_converter*
	_new_converter(const std::string& filepath, ImageFormat format) const;

	/***********************************************************************//*!
	*
	*	@brief Helper method of _new_converter to handle wkhtmltoimage settings.
	*
	*	@param filepath The output file at which to store the converted file.
	*
	*	@param format The image-format to convert to.
	*
	*	@return A pointer to a wkhtmltoimage_global_settings instance.
	*
	***************************************************************************/
	
	virtual wkhtmltoimage_global_settings*
	_new_converter_settings(const std::string& filepath,
							ImageFormat format) const;
	
	/***********************************************************************//*!
	*
	*	@brief A callback for wkhtmltoimage that throws an exception.
	*
	*	@param message The error/warning message from the wkhtmltoimage engine.
	*
	***************************************************************************/
	
	friend void _throw(wkhtmltoimage_converter*, const char* message);

	/***********************************************************************//*!
	*
	*	@brief A callback for wkhtmltoimage that logs a message.
	*
	*	@details The message is written to std::clog.
	*
	*	@param message The error/warning message from the wkhtmltoimage engine.
	*
	***************************************************************************/
	
	friend void _log(wkhtmltoimage_converter*, const char* message);
	
	/*! A instance of the Allocator struct for the V8 engine. */
	mutable Allocator _allocator;

	/*! The virtual environment in which the V8 runs. */
	v8::Isolate* _isolate;
	
	/*! A persistent (i.e. non-expiring/global) handle
	   to the context in which the instance interacts
	   with the V8 engine. */
	v8::UniquePersistent<v8::Context> _persistent_context;
	
	/*! The content of the base stylesheet. */
	std::string _stylesheet;
	
	/*! The additional CSS added via add_css(). */
	std::string _additional_css;
	
	/*! The current WarningBehavior configuration. */
	WarningBehavior _warning_behaviour;
};

#endif /* LATEX_HPP */