#include <iostream>
#include <string>

#include "String/String.h"

int main()
{
	CTL::Dynamic::String a{ "Hi" };
	
	std::string b{ a.Data(), 1 };

	std::cout << a << '\n';
	std::cout << a.Length() << '\n';
	std::cout << a.Capacity() << '\n';

	std::cout << b << '\n';
	std::cout << b.length() << '\n';
	std::cout << b.capacity() << '\n';
}