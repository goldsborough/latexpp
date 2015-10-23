# latexpp

*latexpp* is a first-of-its kind C++ library for generating `LaTeX` equations via C++. It supports conversion of `LaTeX` equations to HTML as well as JPG, PNG and SVG image formats.

## Usage

```C++
#include "latex.hpp"

int main(int argc, const char* argv[])
{
	// Single class
	Latex latex;

	const std::string equation = "\\sum_{i=1}^{N} i = \\frac{n(n + 1)}{2}";

	// Convert to PNG, store in 'equation.png'
	latex.to_png(equation, "equation.png");

	// Convert to HTML, returns a HTML snippet
	std::string html = latex.to_html(equation);
}
```

`equation.png`:

![equation.png](https://raw.githubusercontent.com/goldsborough/latexpp/master/docs/img/equation.png)

## Documentation

You can build extensive documentation with `doxygen`. See the `doxyfile` in the `docs/` folder. There are also some example programs in the `examples` folder.

## LICENSE

This project is released under the [MIT License](http://goldsborough.mit-license.org). For more information, see the LICENSE file.

## Authors

Peter Goldsborough + [cat](https://goo.gl/IpUmJn) :heart:

<a href="https://gratipay.com/~goldsborough/"><img src="http://img.shields.io/gratipay/goldsborough.png?style=flat-square"></a>
