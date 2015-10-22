#include "latex.hpp"

#include <iostream>

int main(int argc, const char* argv[])
{
	Latex a;
	
	{
		Latex latex = a;
		
		latex.png("\\frac{1}{2} + \\pi \\cdot 2",
				  "../../out.png");
		
	}
	a.png("1 - 0 = 1", "../../out2.png");
	
	//std::cout << latex.html("\\frac{1}{2} + \\pi \\cdot 2") << std::endl;
}