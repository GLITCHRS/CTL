#include <iostream>

#include "String/String.h"
#include "Tests.h"

int main()
{
	CTL::Dynamic::String data{ "Hello World!" };

	LOGStr(data);
	data.Reserve(100);
	LOGStr(data);
	data.Shrink(12);
	LOGStr(data);
	data.Shrink(50);
	LOGStr(data);
	data.ShrinkToFit();
	LOGStr(data);
}