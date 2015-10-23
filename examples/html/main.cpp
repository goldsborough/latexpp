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

	// Get a snippet (in a <span>) you can embed
	// in an HTML file with the KaTeX stylesheet
	std::string html_snippet = latex.to_html(equation);

	std::cout << html_snippet << std::endl;

	// Get a complete HTML document (that you can really display
	// in a browser) with embedded CSS stylesheet.
	std::string html_complete = latex.to_complete_html(equation);

	std::ofstream stream("example.html");

	stream << html_complete;
}
