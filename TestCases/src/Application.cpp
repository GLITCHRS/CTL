#include <iostream>
#include "String/String.h"

int main()
{
	CTL::String t0{ "Ahme" };
	CTL::String t1{ std::move(t0) };

	t0 = "Ahme";

	std::cout << t0.Size() << '\n';
	std::cout << t0.Length() << '\n';
	std::cout << t1.Size() << '\n';
	std::cout << t1.Length() << '\n';
}