#include <iostream>

#include "String/String.h"
#include "Tests.h"

int main()
{
	CTL::Dynamic::String data{ "Hello% 180" };

	LOGStr(data);
	LOGStr(data.Capitalize());
	LOGStr(data);
}