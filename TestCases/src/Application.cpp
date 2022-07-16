#include <iostream>

#include "String/String.h"

int main()
{
	CTL::Dynamic::String a{ "Name: {} {}" };
	
	std::cout << a.Format("Ahmed", "Zaki") << '\n';
}