#include <iostream>
#include "String/String.h"

int main()
{
	CTL::String t0{ "Data" };
	CTL::String f{ "ata" };

	std::cout << (t0 * 100) << '\n';
}