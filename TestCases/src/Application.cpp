#include <iostream>
#include "String/String.h"

int main()
{
	CTL::String t0{ "Ahme" };
	t0 += 'd';

	std::cout << (t0) << '\n';
}