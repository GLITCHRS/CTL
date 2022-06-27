#include <iostream>
#include "String/String.h"

int main()
{
	CTL::String t0{ "Data" };

	std::cout << t0 << '\n';
	std::cout << t0.Length() << '\n';
	std::cout << t0.Size() << '\n';

	t0.append(" new Str 1!");

	std::cout << t0 << '\n';
	std::cout << t0.Length() << '\n';
	std::cout << t0.Size() << '\n';

	t0.append(t0);

	std::cout << t0 << '\n';
	std::cout << t0.Length() << '\n';
	std::cout << t0.Size() << '\n';
}