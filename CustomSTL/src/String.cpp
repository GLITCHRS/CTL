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
	String::String() : m_Length(0), m_Count(0), m_Size(sizeof(char) * 15), m_Buffer(static_cast<char*>(_malloca(m_Size)))
	{
		if (m_Buffer)
		{
			memset(m_Buffer, 0, m_Size);
			std::cout << "Constructed " << m_Size << " bytes!\n";
		}
		else
			throw std::bad_alloc();
	}

	String::String(const String& other) : m_Length(other.m_Length), m_Count(other.m_Count), m_Size(other.m_Size), m_Buffer(static_cast<char*>(_malloca(m_Size)))
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

	String::String(size_t length) : m_Length(length), m_Count(length + 1), m_Size(sizeof(char)* m_Count), m_Buffer(static_cast<char*>(_malloca(m_Size)))
	{
		if (m_Buffer)
		{
			memset(m_Buffer, 0, m_Size);
			std::cout << "Constructed " << m_Size << " bytes!\n";
		}
		else
			throw std::bad_alloc();
	}

	String::String(const char* string) : m_Length(strlen(string)), m_Count(m_Length + 1), m_Size(sizeof(char)* m_Count), m_Buffer(static_cast<char*>(_malloca(m_Size)))
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
		m_Length = string.size();
		m_Size = m_Length + 1;
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
	const size_t String::Length() const
	{
		return m_Length;
	}

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
* NON-CONST OPERATORS OVERLOADINGS
* 
*/
namespace CustomSTL
{
	/*
	* 
	* operator[](index)
	* 
	*/
	char& String::operator[](size_t index)
	{
		if(m_Count > index)
			return m_Buffer[index];

		throw std::out_of_range("Index out of bounds!");
	}
}

/*
* 
*	CONST OPERATORS OVERLOADINGS
* 
*/
namespace CustomSTL
{

	/*
	*
	* operator[](index)
	*
	*/
	const char& String::operator[](size_t index) const
	{
		if (m_Count > index)
			return m_Buffer[index];

		throw std::out_of_range("Index out of bounds!");
	}

	/*
	*
	*	operator+()
	*
	*/
	String String::operator+(const char* string) const
	{
		String newStr{ m_Length + strlen(string) };

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
		const size_t strSize{ strlen(string) };

		if (m_Length != strSize)
			return false;

		for (size_t i{}; i < m_Count; ++i)
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
	*	operator!=()
	*
	*/

	bool String::operator!=(const char* string) const
	{
		return !(*this == string);
	}

	bool String::operator!=(const std::string& string) const
	{
		return !(*this == string.data());
	}

	bool String::operator!=(const String& other) const
	{
		return !(*this == other.m_Buffer);
	}

	/*
	*
	*	operator>()
	*
	*/

	bool String::operator>(const char* string) const
	{
		const size_t strSize{ strlen(string) };

		if (m_Length > strSize)
			return true;

		else if (m_Length < strSize)
			return false;

		for (size_t i{}; i < m_Count; ++i)
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
	*	operator<()
	*
	*/

	bool String::operator<(const char* string) const
	{
		return !(*this >= string);
	}

	bool String::operator<(const std::string& string) const
	{
		return !(*this >= string);
	}

	bool String::operator<(const String& other) const
	{
		return !(*this >= other);
	}

	/*
	*
	*	operator>=()
	*
	*/

	bool String::operator>=(const char* string) const
	{
		const String& self{ *this };

		return (self > string || self == string);
	}

	bool String::operator>=(const std::string& string) const
	{
		const String& self{ *this };
		const char* data{ string.data() };

		return (self > data || self == data);
	}

	bool String::operator>=(const String& other) const
	{
		const String& self{ *this };

		return (self > other.m_Buffer || self == other.m_Buffer);
	}

	/*
	*
	*	operator<=()
	*
	*/

	bool String::operator<=(const char* string) const
	{
		return !(*this > string);
	}

	bool String::operator<=(const std::string& string) const
	{
		return !(*this > string.data());
	}

	bool String::operator<=(const String& other) const
	{
		return !(*this > other.m_Buffer);
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