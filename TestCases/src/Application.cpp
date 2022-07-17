#include <iostream>

#include "String/String.h"

int main()
{
	CTL::Dynamic::String a{ "Name: {} {} 2" };
	
	std::cout << a.Format("Ahmed", "Zaki") << '\n';
}