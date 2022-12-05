#include <iostream>
#include <string>
#include <array>

#include "Iterables/Dynamic/String.h"
#include "Iterables/Dynamic/Array.h"

int main()
{
	CTL::Dynamic::Array<int> a{1, 2, 3};

	std::cout << a << '\n';
}