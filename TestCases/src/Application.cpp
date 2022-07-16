#include <iostream>

#include "String/String.h"

int main()
{
	CTL::Dynamic::String a{ "Ahmed" };

	std::cout << a.SubStr(2, 5) << '\n';
}