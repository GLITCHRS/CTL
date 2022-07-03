// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#pragma once

#ifdef _MSVC_LANG
// if C++20 or later is being used.
#if _MSVC_LANG > 202002L
#define CONSTEXPR20 constexpr
#define AllocStr(VAR, SIZE, AUTOINIT) if(AUTOINIT) VAR = new (std::nothrow) char[SIZE]{}; else VAR = new (std::nothrow) char[SIZE];
#define DeallocStr(VAR) delete[] VAR; VAR = nullptr
#else
#define CONSTEXPR20 inline
#define AllocStr(VAR, SIZE, AUTOINIT) VAR = static_cast<char*>(_malloca(SIZE)); if(AUTOINIT && VAR) \
			for(size_t i{}; i < (SIZE / sizeOfChar); ++i) VAR[i] = '\0';
#define DeallocStr(VAR) _freea(VAR); VAR = nullptr
#endif

// if C++17 or later is being used.
#if _MSVC_LANG >= 202002L
#define CONSTINIT constinit
#else
#define CONSTINIT const
#endif
#endif

#include <iostream>
#include <cstring>


namespace CTL
{
	CONSTINIT size_t sizeOfChar{ sizeof(char) };

	/*
	*
	*	length function
	*
	*/
	CONSTEXPR20 size_t GetCStrLength(const char* str)
	{
		return *str ? 1 + GetCStrLength(str + 1) : 0;
	}

	class String
	{
		friend std::ostream& operator<<(std::ostream& stream, const String& data);

	public:
		/*
		*
		*	IMPLICIT CONSTRUCTORS
		*
		*/

		CONSTEXPR20 String() : m_Length(0), m_Size(sizeOfChar * 15)
		{
			AllocStr(m_Buffer, m_Size, true);

			if(!m_Buffer)
			{
				m_Length = 0;
				m_Size = 0;
				throw std::bad_alloc();
			}
		}

		/*
		*
		*	EXPLICIT CONSTRUCTORS
		*
		*/

		CONSTEXPR20 explicit String(size_t requiredLength) : m_Length(0), m_Size(sizeOfChar* (requiredLength + 1))
		{
			AllocStr(m_Buffer, m_Size, true);

			if (!m_Buffer)
			{
				m_Length = 0;
				m_Size = 0;
				throw std::bad_alloc();
			}
		}

		CONSTEXPR20 explicit String(const char* string, const size_t requiredSize = 0)
		{
			m_Length = GetCStrLength(string);
			size_t stringSize{ (m_Length + 1) * sizeOfChar };
			m_Size = (requiredSize != 0) ? requiredSize : stringSize;

			if (m_Size < stringSize)
				throw std::bad_array_new_length();
			else
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
		}

		CONSTEXPR20 explicit String(const std::string& string) : m_Length(string.size()), m_Size(m_Length + 1)
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
		*	COPY CONSTRUCTOR
		* 
		*/

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
		*	MOVE CONSTRUCTOR
		*
		*/

		CONSTEXPR20 String(String&& string) noexcept : m_Length(string.m_Length), m_Size(string.m_Size)
		{
			m_Buffer = string.m_Buffer;

			AllocStr(string.m_Buffer, 15 * sizeOfChar, true);
			string.m_Length = 0;
		}

		/*
		*
		*	.reserve method
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
		*	.append method
		*
		*/
		CONSTEXPR20 void append(const char* string, const size_t requiredSize = 0)
		{
			size_t strLength{ GetCStrLength(string) };
			size_t strSize{ (m_Length + strLength + 1) * sizeOfChar };

			if (m_Size < strSize)
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

		/*
		*
		*	.Has method
		*
		*/

		CONSTEXPR20 bool Has(const char character) const
		{
			for (size_t i{}; i < m_Length; ++i)
				if (m_Buffer[i] == character)
					return true;

			return false;
		}

		CONSTEXPR20 bool Has(const char* string) const
		{
			size_t strLength{ GetCStrLength(string) };

			if (m_Length < strLength)
				return false;

			for (size_t i{}; i < m_Length; ++i)
			{
				size_t i_cpy{ i }, j{};
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

		/*
		*
		*	.Count method
		*
		*/

		CONSTEXPR20 unsigned int Count(const char character) const
		{
			unsigned int count{};

			for (size_t i{}; i < m_Length; ++i)
				if (m_Buffer[i] == character)
					++count;

			return count;
		}

		CONSTEXPR20 unsigned int Count(const char* string) const
		{
			size_t strLength{ GetCStrLength(string) };

			if (m_Length < strLength)
				return 0;

			unsigned int count{};
			for (size_t i{}; i < m_Length; ++i)
			{
				size_t i_cpy{ i }, j{};

				while (j < strLength && m_Buffer[i_cpy] == string[j])
					++i_cpy, ++j;

				if (j == strLength)
					++count;
			}

			return count;
		}

		CONSTEXPR20 unsigned int Count(const std::string& string) const
		{
			return Count(string.data());
		}

		CONSTEXPR20 unsigned int Count(const CTL::String& string) const
		{
			return Count(string.Data());
		}

		/*
		*
		*	.begin/end methods
		*
		*/

		CONSTEXPR20 char* begin()
		{
			return m_Buffer;
		}

		CONSTEXPR20 char* end()
		{
			return m_Buffer + m_Length;
		}

		CONSTEXPR20 const char* begin() const
		{
			return m_Buffer;
		}

		CONSTEXPR20 const char* end() const
		{
			return m_Buffer + m_Length;
		}

		/*
		*
		*	.Data method
		*
		*/

		CONSTEXPR20 char* Data()
		{
			return m_Buffer;
		}

		CONSTEXPR20 const char* Data() const
		{
			return m_Buffer;
		}

		/*
		*
		*	.Length method
		*
		*/

		CONSTEXPR20 const size_t Length() const
		{
			return m_Length;
		}

		/*
		*
		*	.Size method
		*
		*/

		CONSTEXPR20 const size_t Size() const
		{
			return m_Size;
		}

		/*
		*
		*	operator[](index)
		*
		*/

		CONSTEXPR20 char& operator[](size_t index)
		{
			if (m_Length > index)
				return m_Buffer[index];

			throw std::out_of_range("Index out of bounds!");
		}

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

		CONSTEXPR20 String operator+(const char character) const
		{
			String newStr{ m_Buffer, (m_Length + sizeOfChar + 1) * sizeOfChar};
			newStr.append({ character, '\0' });

			return newStr;
		}

		CONSTEXPR20 String operator+(const char* string) const
		{
			String newStr{ m_Buffer, (m_Length + GetCStrLength(string) + 1) * sizeOfChar };
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
			size_t strLength{ GetCStrLength(string) };
			size_t strSize{ (strLength + 1) * sizeOfChar };

			if (strSize > m_Size)
			{
				size_t sizeToAlloc{ strSize * 2 - 1 };
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
		*	operator+=(string)
		*
		*/

		CONSTEXPR20 void operator+=(const char character)
		{
			this->append({ character, '\0' });
		}

		CONSTEXPR20 void operator+=(const char* string)
		{
			this->append(string);
		}

		CONSTEXPR20 void operator+=(const std::string& string)
		{
			return this->append(string.data());
		}

		CONSTEXPR20 void operator+=(const String& string)
		{
			return this->append(string.m_Buffer);
		}

		/*
		*
		*	operator*=()
		*
		*/
		CONSTEXPR20 void operator*=(size_t count)
		{
			char* currentStr;

			AllocStr(currentStr, m_Size, false);

			if (currentStr)
			{
				for (size_t i{}; i < m_Length; ++i)
					currentStr[i] = m_Buffer[i];

				currentStr[m_Length] = '\0';
			}
			else
				throw std::bad_alloc();

			this->reserve(m_Size * count);

			while (count > 1)
			{
				this->append(currentStr);
				--count;
			}
		}

		/*
		*
		*	operator==()
		*
		*/

		CONSTEXPR20 bool operator==(const char* string) const
		{
			if (m_Length != GetCStrLength(string))
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