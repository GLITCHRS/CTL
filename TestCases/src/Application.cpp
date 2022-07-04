#include <iostream>
#include "String/String.h"

int main()
{
	using namespace std::string_literals;
	using namespace std::string_literals;

	CTL::Dynamic::String t0{ "Helloe"DS };

	std::cout << t0.Length() << '\n';
	std::cout << t0.Size() << '\n';
}