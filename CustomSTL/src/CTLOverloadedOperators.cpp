#include "String/String.h"

/*
*
*	operator<<(cout)
*
*/

std::ostream& operator<<(std::ostream& stream, const CTL::Dynamic::String& data)
{
	stream << data.Data();
	return stream;
}