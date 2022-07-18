#include <iostream>

#include "String/String.h"
#include "Tests.h"

int main()
{
	const CTL::Dynamic::String a{ "Ahmed Zaki" };
	const char* data{ a.SubStr(4, 10) };

	if(data)
		std::cout << data << '\n';
}