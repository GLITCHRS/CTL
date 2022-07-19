#include <iostream>

#include "String/String.h"
#include "Tests.h"

int main()
{
	CTL::Dynamic::String data{ "{}" };
	std::cout << data.Format("Ahmed", "Zaki") << '\n';
}