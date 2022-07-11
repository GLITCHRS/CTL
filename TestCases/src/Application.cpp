#include <iostream>
#include "String/String.h"

void PrintStr(const CTL::Dynamic::String& str)
{
	std::cout << str << '\n';
	std::cout << str.Length() << '\n';
	std::cout << str.Size() << '\n';
}

int main()
{
	const CTL::Dynamic::String data{ "Hello World" };

	std::cout << data.Find('o') << '\n';
	std::cout << data.Find("o W") << '\n';
	std::cout << data.Find("Worl") << '\n';
	std::cout << data.Find("World") << '\n';
	//std::cout << data.Find("Worlds") << '\n';
}