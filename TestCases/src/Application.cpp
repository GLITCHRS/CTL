#include <iostream>
#include "String/String.h"

int main()
{
	CustomSTL::String name{ "Ahmed" };

	std::cout << name.Has('a') << '\n';
}