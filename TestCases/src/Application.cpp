#include <iostream>
#include "String/String.h"

void Print(const CustomSTL::String & tryy)
{

}

int main()
{
	CustomSTL::String name{ "mAmedhmed" };
	CustomSTL::String find{ "med" };

	std::cout << name.Has("med") << '\n';
	std::cout << name.Has(std::string{ "med" }) << '\n';
	std::cout << name.Has(find) << '\n';

	Print(name);
}