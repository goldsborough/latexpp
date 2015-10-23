#include "latex.hpp"

#include <boost/filesystem.hpp>
#include <iostream>

int main(int argc, const char* argv[])
{
	Latex latex;
	
	latex.to_png("1 - 0 = 1", "../../out2.png");
	
	std::cout << latex.to_html("\\frac{1}{2} + \\pi \\cdot 2") << std::endl;
}