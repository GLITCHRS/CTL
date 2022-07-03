#include <iostream>
#include "String/String.h"

int main()
{
	CTL::String t0{ "Ahme" };
	CTL::String t1{ std::move(t0) };

	std::cout << t0 << '\n';
	std::cout << t1 << '\n';
}