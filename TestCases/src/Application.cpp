#include <iostream>
#include "String/String.h"

int main()
{
	CustomSTL::String name{ "mAmedhmed" };

	std::cout << name << '\n';
	std::cout << name.Has("hmed") << '\n';
}