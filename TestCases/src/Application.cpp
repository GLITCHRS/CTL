#include <iostream>
#include "String/String.h"

int main()
{
	CustomSTL::String name{ "Hello W Worl World" };

	std::cout << name.Has("World") << '\n';
	std::cout << name.Has("Worl") << '\n';
	std::cout << name.Has("ld") << '\n';
	std::cout << name.Has("d") << '\n';
	std::cout << name.Has("Hello W") << '\n';
	std::cout << name.Has("Hello") << '\n';
	std::cout << name.Has("HellW") << '\n';
}