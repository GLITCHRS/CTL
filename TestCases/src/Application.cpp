#include <iostream>
#include <string>

#include "Iterables/Dynamic/Array.h"

int main()
{
	int arr[]{ 1, 2, 3 };

	CTL::Dynamic::Array<int> a{ arr };

	std::cout << a << '\n';
	std::cout << a.Length() << '\n';
	std::cout << a.Capacity() << '\n';
}