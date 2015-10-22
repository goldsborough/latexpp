#include "latex.hpp"

#include <iostream>

int main(int argc, const char* argv[])
{
	Latex latex;
	
	std::cout << latex.render("\\frac{1}{2}") << std::endl;
}