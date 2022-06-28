#include <iostream>
#include "String/String.h"

int main()
{
	CTL::String t0{ "Data" };

	std::cout << t0 << '\n';
	std::cout << t0.Length() << '\n';
	std::cout << t0.Size() << '\n';

	t0 = "Test1";

	std::cout << t0 << '\n';
	std::cout << t0.Length() << '\n';
	std::cout << t0.Size() << '\n';

	t0 = "Test2 which is a lot longer than Test1!";

	std::cout << t0 << '\n';
	std::cout << t0.Length() << '\n';
	std::cout << t0.Size() << '\n';
}