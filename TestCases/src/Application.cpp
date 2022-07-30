#include <iostream>

#include "String/String.h"
#include "Tests.h"

int main()
{
	CTL::Dynamic::String data{ "Hello" };

	LOGStr(data);

	data.Append('c');

	LOGStr(data);
}