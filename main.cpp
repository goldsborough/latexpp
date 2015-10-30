#include "latex.hpp"

#include <boost/filesystem.hpp>
#include <iostream>

int main(int argc, const char* argv[])
{
	Latex latex;
	
	std::cout << latex.to_html("\\frac{1}{2} + \\pi \\cdot 2") << std::endl;
}