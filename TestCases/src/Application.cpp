#include <iostream>
#include "String/String.h"

int main()
{
	CTL::String t0{ "Hello" };

	t0 = "Hello World";

	std::cout << t0 << '\n';
}