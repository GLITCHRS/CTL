#include <iostream>
#include <string>

#include "Tests.h"

int main()
{
	CTL::Dynamic::String data{ "abcde" };
	CTL::Dynamic::String data2{ data.Replace("b", "Hello World!")};

	LOGStr(data);
	LOGStr(data2);
	LOGStr(data);
	std::cout << data.Index(data) << '\n';
}