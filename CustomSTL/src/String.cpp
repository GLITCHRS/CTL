#include <iostream>
#include <cstring>

#include "String/String.h"

/*
*
*	CONSTRUCTORS
*
*/
namespace CTL
{
	String::String() : m_Length(0), m_Size(sizeof(char) * 15), m_Buffer(static_cast<char*>(_malloca(m_Size)))
	{
		if (m_Buffer)
		{
			memset(m_Buffer, 0, m_Size);
			std::cout << "Constructed " << m_Size << " bytes!\n";
		}
		else
			throw std::bad_alloc();
	}

	String::String(const String& other) : m_Length(other.m_Length), m_Size(other.m_Size), m_Buffer(static_cast<char*>(_malloca(m_Size)))
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

	String::String(size_t length) : m_Length(0), m_Size(sizeof(char)* (length + 1)), m_Buffer(static_cast<char*>(_malloca(m_Size)))
	{
		if (m_Buffer)
		{
			memset(m_Buffer, 0, m_Size);
			std::cout << "Constructed " << m_Size << " bytes!\n";
		}
		else
			throw std::bad_alloc();
	}

	String::String(const char* string) : m_Length(strlen(string)), m_Size(sizeof(char)* (m_Length + 1)), m_Buffer(static_cast<char*>(_malloca(m_Size)))
	{
		if (m_Buffer)
		{
			strcpy_s(m_Buffer, m_Size, string);
			std::cout << "Constructed " << m_Size << " bytes!\n";
		}
		else
			throw std::bad_alloc();
	}

	String::String(const std::string& string): m_Length(string.size()), m_Size(m_Length + 1), m_Buffer(static_cast<char*>(_malloca(m_Size)))
	{
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
*	NON-CONST METHODS
*
*/
namespace CTL
{

	/*
	* 
	* .reserve method
	* 
	*/
	bool String::reserve(const size_t size)
	{
		if (size < m_Size)
			return false;

		if (m_Length == 0)
		{
			_freea(m_Buffer);
			m_Buffer = static_cast<char*>(_malloca(size));

			if (m_Buffer)
				m_Size = size;
			else
				throw std::bad_alloc();
		}
		else
		{
			char* oldStr{ m_Buffer };
			m_Buffer = static_cast<char*>(_malloca(size));

			if (m_Buffer)
			{
				strcpy_s(m_Buffer, size, oldStr);
				m_Size = size;

				_freea(oldStr);
			}
			else
			{
				_freea(oldStr);
				throw std::bad_alloc();
			}
		}

		return true;
	}

	/*
	* 
	* .append method
	* 
	*/
	void String::append(const char* string, const size_t requiredSize)
	{
		size_t strLength{ strlen(string) };
		size_t strSize{ (m_Length + strLength + 1) * sizeof(char) };

		if (strSize > m_Size)
		{
			char* oldStr = m_Buffer;
			size_t newStrSize{ (requiredSize != 0) ? requiredSize : strSize * 2 };

			std::cout << "New strSize: " << newStrSize << '\n';

			m_Buffer = static_cast<char*>(_malloca(newStrSize));
			if (m_Buffer)
			{
				strcpy_s(m_Buffer, newStrSize, oldStr);
				strcat_s(m_Buffer, newStrSize, string);

				m_Length += strLength;
				m_Size = newStrSize;

				_freea(oldStr);
			}
			else
			{
				_freea(oldStr);
				throw std::bad_alloc();
			}
		}
		else
		{
			strcat_s(m_Buffer, m_Size, string);
			m_Length += strLength;
		}
	}

	void String::append(const std::string& string, const size_t requiredSize)
	{
		append(string.data(), requiredSize);
	}

	void String::append(const String & string, const size_t requiredSize)
	{
		append(string.m_Buffer, requiredSize);
	}
}

/*
*
*	CONST METHODS
*
*/
namespace CTL
{
	bool String::Has(const char character) const
	{
		for (size_t i{}; i < m_Length; ++i)
			if (m_Buffer[i] == character)
				return true;

		return false;
	}

	bool String::Has(const char* string) const
	{
		size_t strCount{ strlen(string) };

		for (size_t i{}; i < m_Length; ++i)
		{
			size_t j{};
			while (j < strCount && m_Buffer[i] == string[j]) ++i, ++j;

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
*	NON-CONST GETTERS
*
*/
namespace CTL
{
	char* String::begin()
	{
		return m_Buffer;
	}

	char* String::end()
	{
		return m_Buffer + m_Length;
	}
}

/*
*
*	CONST GETTERS
*
*/
namespace CTL
{
	const char* String::begin() const
	{
		return m_Buffer;
	}

	const char* String::end() const
	{
		return m_Buffer + m_Length;
	}

	const size_t String::Length() const
	{
		return m_Length;
	}

	const size_t String::Size() const
	{
		return m_Size;
	}
}

/*
* 
* NON-CONST OPERATORS OVERLOADINGS
* 
*/
namespace CTL
{
	/*
	* 
	* operator[](index)
	* 
	*/
	char& String::operator[](size_t index)
	{
		if(m_Length > index)
			return m_Buffer[index];

		throw std::out_of_range("Index out of bounds!");
	}
}

/*
* 
*	CONST OPERATORS OVERLOADINGS
* 
*/
namespace CTL
{

	/*
	*
	* operator[](index)
	*
	*/
	const char& String::operator[](size_t index) const
	{
		if (m_Length > index)
			return m_Buffer[index];

		throw std::out_of_range("Index out of bounds!");
	}

	/*
	*
	*	operator+(string)
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
	*	operator*(string)
	*
	*/

	String String::operator*(size_t count) const
	{
		if (m_Length == 0)
			return String{ 1 };

		String newStr{ count * m_Length };
		char* thisStr{ this->m_Buffer };

		while (count-- > 0)
			newStr.append(thisStr);

		return newStr;
	}

	/*
	*
	*	operator==()
	*
	*/

	bool String::operator==(const char* string) const
	{
		if (m_Length != strlen(string))
			return false;

		for (size_t i{}; i < m_Length; ++i)
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
		for (size_t i{}; i < m_Length; ++i)
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
namespace CTL
{
	String::~String()
	{
		std::cout << "Destructing " << m_Size << " bytes!\n";

		_freea(m_Buffer);
		m_Buffer = nullptr;
	}
}