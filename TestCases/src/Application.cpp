#include <iostream>

#include "String/String.h"
#include "Tests.h"

int main()
{
	CTL::Dynamic::String data{ "Hello World!" };

	LOGStr(data);
	data.AppendAll("String1", "String2");
	LOGStr(data);
}