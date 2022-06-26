#include <iostream>
#include "String/String.h"

int main()
{
	CTL::String name1{"Ahmed"};

	for (char& item : name1)
		std::cout << item << '\n';
}