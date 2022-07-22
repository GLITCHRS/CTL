#include <iostream>

#include "String/String.h"
#include "Tests.h"

int main()
{
	CTL::Dynamic::String data{ "Creator-{}" };
	std::cout << data.Format("K999") << '\n';
	std::cout << data << '\n';
}