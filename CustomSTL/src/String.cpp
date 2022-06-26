#include <iostream>
#include <cstring>

#include "String/String.h"

/*
*
*	CONSTRUCTORS
*
*/
namespace CustomSTL
{
	String::String() : m_Count(0), m_Size(sizeof(char) * 15), m_Buffer(static_cast<char*>(_malloca(m_Size)))
	{
		if (m_Buffer)
		{
			memset(m_Buffer, 0, m_Size);
			std::cout << "Constructed " << m_Size << " bytes!\n";
		}
		else
			throw std::bad_alloc();
	}

	String::String(const String& other) : m_Count(other.m_Count), m_Size(other.m_Size), m_Buffer(static_cast<char*>(_malloca(m_Size)))
	{
		if (m_Buffer)
		{
			strcpy_s(m_Buffer, m_Size, other.m_Buffer);
			std::cout << "Constructed " << m_Size << " bytes!\n";
		}
		else
			throw std::bad_alloc();
	}


	/*
	* 
	* EXPLICIT CONSTRUCTORS
	* 
	*/

	String::String(size_t count) : m_Count(count + 1), m_Size(sizeof(char)* m_Count), m_Buffer(static_cast<char*>(_malloca(m_Size)))
	{
		if (m_Buffer)
		{
			memset(m_Buffer, 0, m_Size);
			std::cout << "Constructed " << m_Size << " bytes!\n";
		}
		else
			throw std::bad_alloc();
	}

	String::String(const char* string) : m_Count(strlen(string) + 1), m_Size(sizeof(char)* m_Count), m_Buffer(static_cast<char*>(_malloca(m_Size)))
	{
		if (m_Buffer)
		{
			strcpy_s(m_Buffer, m_Size, string);
			std::cout << "Constructed " << m_Size << " bytes!\n";
		}
		else
			throw std::bad_alloc();
	}

	String::String(const std::string& string)
	{
		m_Size = string.size() + 1;
		m_Count = m_Size / sizeof(char);
		m_Buffer = static_cast<char*>(_malloca(m_Size));

		if (m_Buffer)
		{
			strcpy_s(m_Buffer, m_Size, string.data());
			std::cout << "Constructed " << m_Size << " bytes!\n";
		}
		else
			throw std::bad_alloc();
	}
};

/*
*
*	CONST GETTERS
*
*/
namespace CustomSTL
{
	const size_t String::Count() const
	{
		return m_Count;
	}

	const size_t String::Size() const
	{
		return m_Size;
	}
}

/*
*
*	CONST METHODS
*
*/
namespace CustomSTL
{
	bool String::Has(const char character) const
	{
		for (size_t i{}; i < m_Count; ++i)
			if (m_Buffer[i] == character)
				return true;

		return false;
	}

	bool String::Has(const char* string) const
	{
		size_t strCount{ strlen(string) };

		for (size_t i{}; i < m_Count; ++i)
		{
			size_t j{};

			while (j < strCount && m_Buffer[i] == string[j])
				++i, ++j;

			if (j == strCount)
				return true;
		}
		return false;
	}

	bool String::Has(const std::string& string) const
	{
		return Has(string.data());
	}

	bool String::Has(const String& string) const
	{
		return Has(string.m_Buffer);
	}
}

/*
* 
*	OPERATORS OVERLOADINGS
* 
*/
namespace CustomSTL
{

	/*
	*
	*	operator+()
	*
	*/

	String String::operator+(const char* string) const
	{
		String newStr{ (m_Count + strlen(string)) - 1 };

		strcat_s(newStr.m_Buffer, newStr.m_Size, m_Buffer);
		strcat_s(newStr.m_Buffer, newStr.m_Size, string);

		return newStr;
	}

	String String::operator+(const std::string& string) const
	{
		return (*this + string.data());
	}

	String String::operator+(const String& other) const
	{
		return (*this + other.m_Buffer);
	}

	/*
	*
	*	operator==()
	*
	*/

	bool String::operator==(const char* string) const
	{
		for (size_t i{}; i < m_Count && i < strlen(string) + 1; ++i)
			if (m_Buffer[i] != string[i])
				return false;

		return true;
	}

	bool String::operator==(const std::string& string) const
	{
		return (*this == string.data());
	}

	bool String::operator==(const String& other) const
	{
		return (*this == other.m_Buffer);
	}

	/*
	*
	*	operator>=()
	*
	*/

	bool String::operator>=(const char* string) const
	{
		for (size_t i{}; i < m_Count && i < strlen(string) + 1; ++i)
			if (m_Buffer[i] < string[i])
				return false;

		return true;
	}

	bool String::operator>=(const std::string& string) const
	{
		return (*this >= string.data());
	}

	bool String::operator>=(const String& other) const
	{
		return (*this >= other.m_Buffer);
	}

	/*
	*
	*	operator<=()
	*
	*/

	bool String::operator<=(const char* string) const
	{
		for (size_t i{}; i < m_Count && i < strlen(string) + 1; ++i)
			if (m_Buffer[i] > string[i])
				return false;

		return true;
	}

	bool String::operator<=(const std::string& string) const
	{
		return (*this <= string.data());
	}

	bool String::operator<=(const String& other) const
	{
		return (*this <= other.m_Buffer);
	}

	/*
	*
	*	operator>()
	*
	*/

	bool String::operator>(const char* string) const
	{
		for (size_t i{}; i < m_Count && i < strlen(string) + 1; ++i)
			if (m_Buffer[i] > string[i])
				return true;

		return false;
	}

	bool String::operator>(const std::string& string) const
	{
		return (*this > string.data());
	}

	bool String::operator>(const String& other) const
	{
		return (*this > other.m_Buffer);
	}

	/*
	*
	*	operator<<(cout)
	*
	*/
	std::ostream& operator<<(std::ostream& stream, const String& data)
	{
		stream << data.m_Buffer;
		return stream;
	}
}

/*
*
*	Destructor
*
*/
namespace CustomSTL
{
	String::~String()
	{
		std::cout << "Destructing " << m_Size << " bytes!\n";

		_freea(m_Buffer);
		m_Buffer = nullptr;
	}
}