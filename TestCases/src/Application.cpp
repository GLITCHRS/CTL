#include <iostream>
#include <string>

#include "Tests.h"

int main()
{
	CTL::Dynamic::String a{ "ahmed" };

	a.Reserve(100);

	a.Shrink(6);
}