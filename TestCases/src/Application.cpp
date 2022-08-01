#include <iostream>

#include "String/String.h"
#include "Tests.h"

int main()
{
	CTL::Dynamic::String data{ "Hello World!" };

	LOGStr(data);
	LOGStr(data.SubStrC(6, 7));
	LOGStr(data);
}