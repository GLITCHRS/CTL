#include <iostream>

#include "String/String.h"
#include "Tests.h"

int main()
{
	CTL::Dynamic::String data{ "Hello {}{}" };

	LOGStr(data);
	LOGStr(data.Format("World", "!"));
	LOGStr(data);
	LOGStr(data.Format("World", "!"));
	LOGStr(data);
}