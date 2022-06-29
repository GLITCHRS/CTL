#include <iostream>
#include "String/String.h"

int main()
{
	CTL::String t0{ "Ahme" };

	std::cout << t0 << '\n';
	std::cout << t0.Length() << '\n';
	std::cout << t0.Size() << '\n';
	std::cout << t0.Has("me") << '\n';

	t0 *= 5;

	std::cout << t0 << '\n';
	std::cout << t0.Length() << '\n';
	std::cout << t0.Size() << '\n';
	std::cout << t0.Has("me") << '\n';
}