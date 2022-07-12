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

	PrintStr(data);
	std::cout << data.Index('o') << '\n';
	std::cout << data.Index("o W") << '\n';
	std::cout << data.Index("Worl") << '\n';
	std::cout << data.Index("World") << '\n';
	std::cout << data.Index("Worlds") << '\n';
}