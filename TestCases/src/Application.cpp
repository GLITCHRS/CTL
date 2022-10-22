#include <iostream>
#include <string>

#include "Tests.h"

int main()
{
	CTL::Dynamic::String a{ "ahmed {} {}" };

	LOGStr(a.Replace("{}", "Hello!"));
}