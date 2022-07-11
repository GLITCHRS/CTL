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
	CTL::Dynamic::String data{ "Hello" };

	PrintStr(data);
	data.append(" World!");
	PrintStr(data);
}