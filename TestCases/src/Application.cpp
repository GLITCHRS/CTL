#include <iostream>

#include "String/String.h"
#include "Tests.h"

int main()
{
	CTL::Dynamic::String data{ "15 hello% 180" };

	LOGStr(data);
	LOGStr(data.ToUpper());
	LOGStr(data);
}