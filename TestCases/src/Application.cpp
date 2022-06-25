#include <iostream>
#include "String/String.h"

int main()
{
	CustomSTL::String name1{};
	CustomSTL::String name2{ 15 };
	CustomSTL::String name3{ "mAmedhmed" };
	CustomSTL::String name4{ std::string{"Hello World!"} };
	CustomSTL::String name5{ name3 };

	std::cout << name1 << '\n';
	std::cout << name2 << '\n';
	std::cout << name3 << '\n';
	std::cout << name4 << '\n';
	std::cout << name5 << '\n';
}