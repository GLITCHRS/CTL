#include <iostream>
#include "String/String.h"

int main()
{
	CTL::String t0{ "Ahmeedddrefddfe" };
	CTL::String t1{ "hme" };

	std::cout << t0.StartsWith("hme") << '\n';
	std::cout << t0.StartsWith(std::string{ "hme" }) << '\n';
	std::cout << t0.StartsWith(t1) << '\n';
}