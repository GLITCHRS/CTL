#include <iostream>
#include "String/String.h"

int main()
{
	CTL::String t0{ "Hello" };

	std::cout << t0.Has("Hello") << '\n';
}