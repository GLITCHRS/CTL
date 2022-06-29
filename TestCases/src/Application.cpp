#include <iostream>
#include "String/String.h"

int main()
{
	CTL::String t0{ "Ahme" };

	t0 += 'd';

	std::cout << t0 << '\n';
	std::cout << t0.Length() << '\n';
	std::cout << t0.Size() << '\n';
	std::cout << t0.Has("lo") << '\n';
}