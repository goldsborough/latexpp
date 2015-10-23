#include "../../latex.hpp"

#include <fstream>
#include <iostream>
#include <string>

int main(int argc, const char* argv[])
{
	// Instantiate Latex instance
	Latex latex;

	latex.add_css(".latex { color: red; font-size: 50px; }");

	// Arithmetic series. Be sure to escape the backslashes!
	const std::string equation = "\\sum_{i=1}^{N} i = \\frac{n(n + 1)}{2}";

	latex.to_jpg(equation, "equation.jpg");
}
