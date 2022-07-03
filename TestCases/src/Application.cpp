#include <iostream>
#include "String/String.h"

int main()
{
	CTL::String t0{ "Ahmeedddrefddfe" };

	std::cout << t0.Count("dd") << '\n';
}