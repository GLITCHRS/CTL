#include <iostream>

#include "String/String.h"
#include "Tests.h"

int main()
{
	CTL::Dynamic::String data1{ "\nh\thello% 180 hi" };
	CTL::Dynamic::String data2{ "NewStr" };

	data1.Swap(data2);

	LOGStr(data1);
	LOGStr(data2);
}