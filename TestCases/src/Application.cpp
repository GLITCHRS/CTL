#include <iostream>
#include <string>

#include "String/String.h"
#include "Tests.h"

int main()
{
	CTL::Dynamic::String data{ "abcde" };

	LOGStr(data);
	data.InPlaceReplace("bc", "ph");
	LOGStr(data);
}