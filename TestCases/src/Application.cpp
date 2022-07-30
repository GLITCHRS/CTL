#include <iostream>

#include "String/String.h"
#include "Tests.h"

int main()
{
	CTL::Dynamic::String data{ "\nh\thello% 180 hi" };

	LOGStr(data);
	LOGStr(data.Title());
	LOGStr(data);
}