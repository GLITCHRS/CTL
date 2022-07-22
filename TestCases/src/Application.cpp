#include <iostream>

#include "String/String.h"
#include "Tests.h"

int main()
{
	CTL::Dynamic::String data{ "Hello" };

	std::cout << data << '\n';
	std::cout << data.Length() << '\n';
	std::cout << data.Size() << '\n';

	data.Append('c');

	std::cout << data << '\n';
	std::cout << data.Length() << '\n';
	std::cout << data.Size() << '\n';
}