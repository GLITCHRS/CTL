#include <iostream>
#include "String/String.h"

int main()
{
	CTL::String t0{ "Ahme" };
	CTL::String t1{ "Ahme", 15 };
	CTL::String t2{ t0 + "d Zaki" };

	t0 *= 2;

	std::cout << t0 << '\n';
}