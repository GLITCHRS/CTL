#include <iostream>
#include "String/String.h"

int main()
{
	using namespace std::string_literals;

	CTL::String t0{ "Helloe" };

	std::cout << t0.StartsWith('e') << '\n';
	std::cout << t0.EndsWith('o') << '\n';
}