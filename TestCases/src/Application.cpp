#include <iostream>
#include <string>

#include "String/String.h"

int main()
{
	CTL::Dynamic::String a{ "Hi" };
	a.Insert('a', 2);
	std::cout << a << '\n';
	std::cout << a.Length() << '\n';
	std::cout << a.Size() << '\n';
}