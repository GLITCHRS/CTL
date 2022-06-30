#include <iostream>
#include "String/String.h"

int main()
{
	CTL::String t0{ "Ahme" };
	CTL::String t1{ "Ahme", 4 };

	std::cout << (t0 + "d Zaki") << '\n';
}