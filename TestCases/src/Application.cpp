#include <iostream>
#include <string>

#include "Iterables/Dynamic/String.h"
#include "Iterables/Dynamic/Array.h"

int main()
{
	CTL::Dynamic::Array<int>::SetDefaultCapacity(5);
	CTL::Dynamic::Array<int> a{};
	//CTL::Dynamic::Array<int> a2{ 1, 2, 4 };

	std::cout << a << '\n';
	std::cout << a.Length() << '\n';
	std::cout << a.Capacity() << '\n';

	//a.Insert(3, 0);

	//std::cout << "============" << '\n';
	//std::cout << a << '\n';
	//std::cout << a.Length() << '\n';
	//std::cout << a.Capacity() << '\n';

	//std::cout << "============" << '\n';
	//std::cout << a2 << '\n';
	//std::cout << a2.Length() << '\n';
	//std::cout << a2.Capacity() << '\n';
}