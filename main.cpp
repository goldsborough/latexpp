#include "latex.hpp"

#include <iostream>

int main(int argc, const char* argv[])
{
	Latex a;
	
	Latex latex;
	
	latex.png("\\frac{1}{2} + \\pi \\cdot 2",
			  "../../out.png");
	
	//std::cout << latex.html("\\frac{1}{2} + \\pi \\cdot 2") << std::endl;
}