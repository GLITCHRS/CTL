#pragma once

#if _HAS_CXX20
#define CONSTEXPR20 constexpr
#define AllocStr(VAR, SIZE, AUTOINIT) if(AUTOINIT) VAR = new char[SIZE]{}; else VAR = new char[SIZE];
#define DeallocStr(VAR) delete[] VAR; VAR = nullptr
#else
#define CONSTEXPR20 inline
#define AllocStr(VAR, SIZE, AUTOINIT) VAR = static_cast<char*>(_malloca(SIZE)); if(AUTOINIT && VAR) memset(VAR, 0, SIZE)
#define DeallocStr(VAR) _freea(VAR); VAR = nullptr
#endif

#include <iostream>
#include <cstring>

/*
*
*	CONSTRUCTORS
*
*/
namespace CTL
{
	constexpr size_t length(const char* str)
	{
		return *str ? 1 + length(str + 1) : 0;
	}

	class String
	{
		friend std::ostream& operator<<(std::ostream& stream, const String& data);

	public:
		CONSTEXPR20 String() : m_Length(0), m_Size(sizeof(char) * 15)
		{
			AllocStr(m_Buffer, m_Size, true);

			if(!m_Buffer)
			{
				m_Length = 0;
				m_Size = 0;
				throw std::bad_alloc();
			}
		}

		CONSTEXPR20 String(const String& string) : m_Length(string.m_Length), m_Size(string.m_Size)
		{
			AllocStr(m_Buffer, m_Size, false);

			if (m_Buffer)
			{
				for (size_t i{}; i < m_Length; ++i)
					m_Buffer[i] = string[i];

				m_Buffer[m_Length] = '\0';
			}
			else
			{
				m_Length = 0;
				m_Size = 0;
				throw std::bad_alloc();
			}
		}


		/*
		*
		* EXPLICIT CONSTRUCTORS
		*
		*/

		CONSTEXPR20 String(size_t requiredLength) : m_Length(0), m_Size(sizeof(char)* (requiredLength + 1))
		{
			AllocStr(m_Buffer, m_Size, true);

			if (!m_Buffer)
			{
				m_Length = 0;
				m_Size = 0;
				throw std::bad_alloc();
			}
		}

		CONSTEXPR20 String(const char* string)
		{
			m_Length = length(string);
			m_Size = (m_Length + 1) * sizeof(char);
			AllocStr(m_Buffer, m_Size, false);

			if (m_Buffer)
			{
				for (size_t i{}; i < m_Length; ++i)
					m_Buffer[i] = string[i];

				m_Buffer[m_Length] = '\0';
			}
			else
			{
				m_Length = 0;
				m_Size = 0;
				throw std::bad_alloc();
			}
		}

		CONSTEXPR20 String(const std::string& string) : m_Length(string.size()), m_Size(m_Length + 1)
		{
			AllocStr(m_Buffer, m_Size, false);

			if (m_Buffer)
			{
				for (size_t i{}; i < m_Length; ++i)
					m_Buffer[i] = string[i];

				m_Buffer[m_Length] = '\0';
			}
			else
			{
				m_Length = 0;
				m_Size = 0;
				throw std::bad_alloc();
			}
		}

		/*
		*
		* .reserve method
		*
		*/
		CONSTEXPR20 void reserve(const size_t size)
		{
			if (size <= m_Size)
				return;

			if (m_Length == 0)
			{
				DeallocStr(m_Buffer);
				AllocStr(m_Buffer, size, true);

				if (m_Buffer)
					m_Size = size;
				else
				{
					m_Length = 0;
					m_Size = 0;
					throw std::bad_alloc();
				}
			}
			else
			{
				char* oldStr{ m_Buffer };
				AllocStr(m_Buffer, size, false);

				if (m_Buffer)
				{
					for (size_t i{}; i < m_Length; ++i)
						m_Buffer[i] = oldStr[i];

					m_Buffer[m_Length] = '\0';
					m_Size = size;
					DeallocStr(oldStr);
				}
				else
				{
					m_Length = 0;
					m_Size = 0;
					DeallocStr(oldStr);
					throw std::bad_alloc();
				}
			}
		}

		/*
		*
		* .append method
		*
		*/
		CONSTEXPR20 void append(const char* string, const size_t requiredSize = 0)
		{
			size_t strLength{ length(string) };
			size_t strSize{ (m_Length + strLength + 1) * sizeof(char) };

			if (m_Size <= strSize)
			{
				char* oldStr = m_Buffer;
				size_t newStrSize{ (requiredSize != 0) ? requiredSize : strSize * 2 - 1 };

				AllocStr(m_Buffer, newStrSize, false);
				if (m_Buffer)
				{
					for (size_t i{}; i < m_Length; ++i)
						m_Buffer[i] = oldStr[i];

					strLength += m_Length;

					size_t j{};
					for (size_t i{ m_Length }; i < strLength; ++i)
						m_Buffer[i] = string[j++];

					m_Buffer[strLength] = '\0';

					m_Length = strLength;
					m_Size = newStrSize;
					DeallocStr(oldStr);
				}
				else
				{
					DeallocStr(oldStr);
					throw std::bad_alloc();
				}
			}
			else
			{
				strLength += m_Length;

				size_t j{};
				for (size_t i{ m_Length }; i < strLength; ++i)
					m_Buffer[i] = string[j++];
				m_Buffer[strLength] = '\0';

				m_Length = strLength;
			}
		}

		CONSTEXPR20 void append(const std::string& string, const size_t requiredSize = 0)
		{
			append(string.data(), requiredSize);
		}

		CONSTEXPR20 void append(const String& string, const size_t requiredSize = 0)
		{
			append(string.m_Buffer, requiredSize);
		}

		CONSTEXPR20 bool Has(const char character) const
		{
			for (size_t i{}; i < m_Length; ++i)
				if (m_Buffer[i] == character)
					return true;

			return false;
		}

		CONSTEXPR20 bool Has(const char* string) const
		{
			size_t strLength{ length(string) };

			if (m_Length < strLength)
				return false;

			for (size_t i{}; i < m_Length; ++i)
			{
				size_t j{};
				size_t i_cpy{ i };
				while (j < strLength && m_Buffer[i_cpy] == string[j]) ++i_cpy, ++j;

				if (j == strLength)
					return true;
			}
			return false;
		}

		CONSTEXPR20 bool Has(const std::string& string) const
		{
			return Has(string.data());
		}

		CONSTEXPR20 bool Has(const String& string) const
		{
			return Has(string.m_Buffer);
		}

		CONSTEXPR20 char* begin()
		{
			return m_Buffer;
		}

		CONSTEXPR20 char* end()
		{
			return m_Buffer + m_Length;
		}

		CONSTEXPR20 char* Data()
		{
			return m_Buffer;
		}

		CONSTEXPR20 const char* begin() const
		{
			return m_Buffer;
		}

		CONSTEXPR20 const char* end() const
		{
			return m_Buffer + m_Length;
		}

		CONSTEXPR20 const char* Data() const
		{
			return m_Buffer;
		}

		CONSTEXPR20 const size_t Length() const
		{
			return m_Length;
		}

		CONSTEXPR20 const size_t Size() const
		{
			return m_Size;
		}

		/*
		*
		* operator[](index)
		*
		*/
		CONSTEXPR20 char& operator[](size_t index)
		{
			if (m_Length > index)
				return m_Buffer[index];

			throw std::out_of_range("Index out of bounds!");
		}

		/*
		*
		* operator[](index)
		*
		*/
		CONSTEXPR20 const char& operator[](size_t index) const
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
		CONSTEXPR20 String operator+(const char* string) const
		{
			String newStr{ m_Length + length(string) };

			newStr.append(m_Buffer);
			newStr.append(string);

			return newStr;
		}

		CONSTEXPR20 String operator+(const std::string& string) const
		{
			return (*this + string.data());
		}

		CONSTEXPR20 String operator+(const String& string) const
		{
			return (*this + string.m_Buffer);
		}

		/*
		*
		*	operator*(string)
		*
		*/

		CONSTEXPR20 String operator*(size_t count) const
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
		*	operator=(string)
		*
		*/

		CONSTEXPR20 void operator=(const char* string)
		{
			size_t strLength{ length(string) };
			size_t strSize{ strLength * sizeof(char) + 1 };
			size_t sizeToAlloc{ strSize * 2 - 1 };

			if (strSize >= m_Size)
			{
				DeallocStr(m_Buffer);
				AllocStr(m_Buffer, sizeToAlloc, false);

				if (m_Buffer)
				{
					m_Length = strLength;
					m_Size = sizeToAlloc;

					for (size_t i{}; i < strLength; ++i)
						m_Buffer[i] = string[i];
					m_Buffer[m_Length] = '\0';
				}
				else
				{
					m_Length = 0;
					m_Size = 0;
					throw std::bad_alloc();
				}
			}
			else
			{
				m_Length = strLength;

				for (size_t i{}; i < strLength; ++i)
					m_Buffer[i] = string[i];
				m_Buffer[m_Length] = '\0';
			}
		}

		CONSTEXPR20 void operator=(const std::string& string)
		{
			return this->operator=(string.data());
		}

		CONSTEXPR20 void operator=(const String& string)
		{
			return this->operator=(string.m_Buffer);
		}

		/*
		*
		*	operator==()
		*
		*/

		CONSTEXPR20 bool operator==(const char* string) const
		{
			if (m_Length != length(string))
				return false;

			for (size_t i{}; i < m_Length; ++i)
				if (m_Buffer[i] != string[i])
					return false;

			return true;
		}

		CONSTEXPR20 bool operator==(const std::string& string) const
		{
			return this->operator==(string.data());
		}

		CONSTEXPR20 bool operator==(const String& string) const
		{
			return this->operator==(string.m_Buffer);
		}

		/*
		*
		*	operator!=()
		*
		*/

		CONSTEXPR20 bool operator!=(const char* string) const
		{
			return !(*this == string);
		}

		CONSTEXPR20 bool operator!=(const std::string& string) const
		{
			return !(*this == string.data());
		}

		CONSTEXPR20 bool operator!=(const String& string) const
		{
			return !(*this == string.m_Buffer);
		}

		/*
		*
		*	operator>()
		*
		*/

		CONSTEXPR20 bool operator>(const char* string) const
		{
			for (size_t i{}; i < m_Length; ++i)
				if (m_Buffer[i] < string[i])
					return false;

			return true;
		}

		CONSTEXPR20 bool operator>(const std::string& string) const
		{
			return this->operator>(string.data());
		}

		CONSTEXPR20 bool operator>(const String& string) const
		{
			return this->operator>(string.m_Buffer);
		}

		/*
		*
		*	operator<()
		*
		*/

		CONSTEXPR20 bool operator<(const char* string) const
		{
			return !this->operator>=(string);
		}

		CONSTEXPR20 bool operator<(const std::string& string) const
		{
			return !this->operator>=(string.data());
		}

		CONSTEXPR20 bool operator<(const String& string) const
		{
			return !this->operator>=(string.m_Buffer);
		}

		/*
		*
		*	operator>=()
		*
		*/

		CONSTEXPR20 bool operator>=(const char* string) const
		{
			const String& self{ *this };

			return (self > string || self == string);
		}

		CONSTEXPR20 bool operator>=(const std::string& string) const
		{
			const String& self{ *this };
			const char* stringData{ string.data() };

			return (self > stringData || self == stringData);
		}

		CONSTEXPR20 bool operator>=(const String& string) const
		{
			const String& self{ *this };
			const char* stringData{ string.m_Buffer };

			return (self > stringData || self == stringData);
		}

		/*
		*
		*	operator<=()
		*
		*/

		CONSTEXPR20 bool operator<=(const char* string) const
		{
			return !this->operator>(string);
		}

		CONSTEXPR20 bool operator<=(const std::string& string) const
		{
			return !this->operator>(string.data());
		}

		CONSTEXPR20 bool operator<=(const String& string) const
		{
			return !this->operator>(string.m_Buffer);
		}

		CONSTEXPR20 ~String()
		{
			DeallocStr(m_Buffer);
		}

	private:
		size_t m_Length;
		size_t m_Size;
		char* m_Buffer;
	};

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
};