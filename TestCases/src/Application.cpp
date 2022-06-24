#include "String/String.h"

int main()
{
	std::string te{ "Test!" };
	CustomSTL::String a{ te };

	std::cout << a + " Hi" << '\n';
}