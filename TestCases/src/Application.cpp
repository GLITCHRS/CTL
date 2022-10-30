#include <iostream>
#include <string>

#include "String/String.h"

int main()
{
	CTL::Dynamic::String a{ "Hi" };
	CTL::Dynamic::String b{ "Hi" };

	std::cout << (a < b) << '\n';
}