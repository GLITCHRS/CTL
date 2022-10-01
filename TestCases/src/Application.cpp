#include <iostream>
#include <string>

#include "Tests.h"

int main()
{
	CTL::Dynamic::String a{ "Hello {} HH" };
	std::cout << a.Format("Hi") << '\n';
}