#include <iostream>
#include "String/String.h"

int main()
{
	CTL::String t0{ "Hello" };

	t0.reserve(100);
	t0.append("Hel");

	std::cout << t0 << '\n';
	std::cout << t0.Length() << '\n';
	std::cout << t0.Size() << '\n';
	std::cout << t0.Has("lo") << '\n';
}