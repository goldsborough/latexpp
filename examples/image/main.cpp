#include "../../latex.hpp"

#include <fstream>
#include <iostream>
#include <string>

int main(int argc, const char* argv[])
{
	// Instantiate Latex instance
	Latex latex;

	// Arithmetic series. Be sure to escape the backslashes!
	const std::string equation = "\\sum_{i=1}^{N} i = \\frac{n(n + 1)}{2}";

	// First API
	latex.to_png(equation, "equation.png");

	// Second API
	latex.to_image(equation, "equation.jpg", Latex::ImageFormat::JPG);
}
