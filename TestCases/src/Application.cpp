#include <iostream>

#include "String/String.h"
#include "Tests.h"

int main()
{
	CTL::Dynamic::String data{ "Creator-K999" };
	std::cout << data.SubStr(8, data.Length()) << '\n';
	std::cout << data << '\n';
}