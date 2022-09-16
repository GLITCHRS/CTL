#include <iostream>
#include <string>

#include "Tests.h"

int main()
{
	CTL::Dynamic::String a{ "Hello" };
	std::cout << a.Index("l", 3) << '\n';
}