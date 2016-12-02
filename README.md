# latexpp

[![GitHub license](https://img.shields.io/github/license/mashape/apistatus.svg?style=flat-square)](http://goldsborough.mit-license.org)

*latexpp* is a first-of-its kind C++ library for generating `LaTeX` equations via C++. It supports conversion of `LaTeX` equations to HTML as well as JPG, PNG and SVG image formats.

## Usage

```C++
#include "latex.hpp"

int main(int argc, const char* argv[])
{
	// Single class
	Latex latex;

	const std::string equation = "\\sum_{i=1}^{n} i = \\frac{n(n + 1)}{2}";

	// Convert to PNG, store in 'equation.png'
	latex.to_png(equation, "equation.png");

	// Convert to HTML, returns a HTML snippet
	std::string html = latex.to_html(equation);
}
```

`equation.png`:

![equation.png](https://raw.githubusercontent.com/goldsborough/latexpp/master/docs/img/equation.png)

## Implementation Overview

*latexpp* uses [`KaTeX`](https://khan.github.io/KaTeX/) to render `LaTeX` to HTML. Because `KaTeX` is a JavaScript library, *latexpp* uses [Google's V8 engine](https://github.com/v8/v8) to write JavaScript from C++. Image output is enabled by the [wkhtmltox](http://wkhtmltopdf.org) C library.

To build this project, you will need:

* The [Google V8 engine](https://github.com/v8/v8) to compile JavaScript.
* The [wkhtmltox](http://wkhtmltopdf.org) library for image output.
* [Boost](http://www.boost.org) for some cross-platform directory operations (can be dropped as a dependency if platform-indpendence is not required, or when the C++ standard committee decides to roll out boost's filesystem library in the C++ standard library.)

`KaTeX` is not a dependency as it is entirely contained in the `katex` folder.

## Documentation

You can build extensive documentation with `doxygen`. See the `doxyfile` in the `docs/` folder. There are also some example programs in the `examples` folder.

## LICENSE

This project is released under the [MIT License](http://goldsborough.mit-license.org). For more information, see the LICENSE file.

## Authors

[Peter Goldsborough](http://goldsborough.me) + [cat](https://goo.gl/IpUmJn) :heart:

<a href="https://gratipay.com/~goldsborough/"><img src="http://img.shields.io/gratipay/goldsborough.png?style=flat-square"></a>
