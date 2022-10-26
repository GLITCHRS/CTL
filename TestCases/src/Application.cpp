#include <iostream>
#include <string>

#include "String/String.h"

int main()
{
	CTL::Dynamic::String a{ "ahmed Hi khalid {}" };

	std::cout << a + 'h' << '\n';
}