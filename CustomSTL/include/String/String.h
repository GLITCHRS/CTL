// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#pragma once

#ifdef _MSVC_LANG
// if C++20 or later is being used.
#if _MSVC_LANG >= 202002L
#define CONSTEXPR20 constexpr
#define AllocStr(VAR, SIZE, AUTOINIT) if(AUTOINIT) VAR = new (std::nothrow) char[SIZE]{}; else VAR = new (std::nothrow) char[SIZE];
#define DeallocStr(VAR) delete[] VAR; VAR = nullptr
#else
#define CONSTEXPR20 inline
#define AllocStr(VAR, SIZE, AUTOINIT) VAR = static_cast<char*>(_malloca(SIZE)); if(AUTOINIT && VAR) FillWCharacter(m_Buffer, 0, SIZE / sizeof(char) - 1, '\0')
#define DeallocStr(VAR) _freea(VAR); VAR = nullptr
#endif
// if C++17 or later is being used.
#if _MSVC_LANG >= 201703L
#define NODISCARD17 [[nodiscard]]
#else
#define NODISCARD17
#endif
#define FillWCharacter(VAR, START, END, CHARACTER) { size_t i{ START }; for(; i < END; ++i) VAR[i] = CHARACTER; }
#define FillWString(VAR, START, END, STRING) { size_t i{ START }; for(; i < END; ++i) VAR[i] = STRING[i]; }
#else
#error _MSVC_LANG macro is required, please refer to https://docs.microsoft.com/en-us/cpp/preprocessor/predefined-macros?view=msvc-170
#endif

#include <iostream>
#include <cstring>

namespace CTL
{
	namespace Dynamic
	{

		/*
		*
		*	length function
		*
		*/
		CONSTEXPR20 size_t GetCStrLength(const char* str)
		{
			size_t i{};
			while (str[i++] != '\0');

			return i - 1;
		}

		class String
		{

		public:
			/*
			*
			*	IMPLICIT CONSTRUCTORS
			*
			*/

			CONSTEXPR20 String() : m_Length(0), m_Size(sizeof(char) * 15)
			{
				AllocStr(m_Buffer, m_Size, true);

				if (!m_Buffer)
				{
					m_Size = 0;
					throw std::bad_alloc();
				}
			}

			/*
			*
			*	EXPLICIT CONSTRUCTORS
			*
			*/

			CONSTEXPR20 explicit String(size_t requiredLength) : m_Length(0), m_Size(sizeof(char)* (requiredLength + 1))
			{
				AllocStr(m_Buffer, m_Size, true);

				if (!m_Buffer)
				{
					m_Size = 0;
					throw std::bad_alloc();
				}
			}

			CONSTEXPR20 explicit String(const char* string, const size_t requiredSize = 0)
			{
				m_Length = GetCStrLength(string);
				size_t stringSize{ (m_Length + 1) * sizeof(char) };
				m_Size = (requiredSize != 0) ? requiredSize : stringSize;

				if (m_Size < stringSize)
				{
					m_Length = 0;
					m_Size = 0;
					throw std::bad_array_new_length();
				}
				else
				{
					AllocStr(m_Buffer, m_Size, false);

					if (m_Buffer)
					{
						FillWString(m_Buffer, 0, m_Length, string);
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

			CONSTEXPR20 explicit String(const std::string& string) : m_Length(string.size()), m_Size((m_Length + 1) * sizeof(char))
			{
				AllocStr(m_Buffer, m_Size, false);

				if (m_Buffer)
				{
					FillWString(m_Buffer, 0, m_Length, string);
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
					FillWString(m_Buffer, 0, m_Length, string);
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

			CONSTEXPR20 String(String&& string) noexcept : m_Length(string.m_Length), m_Size(string.m_Size), m_Buffer(string.m_Buffer)
			{
				AllocStr(string.m_Buffer, 15 * sizeof(char), true);
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
						FillWString(m_Buffer, 0, m_Length, oldStr);
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
			CONSTEXPR20 void append(const char* string)
			{
				size_t strLength{ GetCStrLength(string) };
				size_t strSize{ (m_Length + strLength + 1) * sizeof(char) };

				if (m_Size < strSize)
				{

					if (m_Length == 0)
					{
						DeallocStr(m_Buffer);
						AllocStr(m_Buffer, strSize, false);

						if (m_Buffer)
						{
							FillWString(m_Buffer, 0, strLength, string);
						}
						else
						{
							m_Size = 0;
							throw std::bad_alloc();
						}
					}
					else
					{
						char* oldStr = m_Buffer;
						size_t newStrSize{ strSize * 2 - 1 };

						AllocStr(m_Buffer, newStrSize, false);
						if (m_Buffer)
						{
							FillWString(m_Buffer, 0, m_Length, oldStr);

							size_t i{ m_Length };
							size_t j{};

							m_Length += strLength;
							for (; i < m_Length; ++i)
								m_Buffer[i] = string[j++];
							m_Buffer[m_Length] = '\0';

							m_Size = newStrSize;
							DeallocStr(oldStr);
						}
						else
						{
							DeallocStr(oldStr);
							throw std::bad_alloc();
						}
					}
				}
				else
				{
					size_t i{ m_Length };
					size_t j{};

					m_Length += strLength;
					for (; i < m_Length; ++i)
						m_Buffer[i] = string[j++];
					m_Buffer[m_Length] = '\0';
				}
			}

			CONSTEXPR20 void append(const std::string& string)
			{
				append(string.data());
			}

			CONSTEXPR20 void append(const String& string)
			{
				append(string.m_Buffer);
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
			*	.Find method
			*
			*/

			CONSTEXPR20 char* Find(const char character)
			{
				for (size_t i{}; i < m_Length; ++i)
					if (m_Buffer[i] == character)
						return (m_Buffer + i);

				return nullptr;
			}

			CONSTEXPR20 char* Find(const char* string)
			{
				size_t strLength{ GetCStrLength(string) };

				if (m_Length < strLength)
					return nullptr;

				for (size_t i{}; i < m_Length; ++i)
				{
					size_t i_cpy{ i }, j{};
					while (j < strLength && m_Buffer[i_cpy] == string[j]) ++i_cpy, ++j;

					if (j == strLength)
						return (m_Buffer + i);
				}
				return nullptr;
			}

			CONSTEXPR20 char* Find(const std::string& string)
			{
				return Find(string.data());
			}

			CONSTEXPR20 char* Find(const String& string)
			{
				return Find(string.m_Buffer);
			}

			CONSTEXPR20 const char* Find(const char character) const
			{
				for (size_t i{}; i < m_Length; ++i)
					if (m_Buffer[i] == character)
						return (m_Buffer + i);

				return nullptr;
			}

			CONSTEXPR20 const char* Find(const char* string) const
			{
				size_t strLength{ GetCStrLength(string) };

				if (m_Length < strLength)
					return nullptr;

				for (size_t i{}; i < m_Length; ++i)
				{
					size_t i_cpy{ i }, j{};
					while (j < strLength && m_Buffer[i_cpy] == string[j]) ++i_cpy, ++j;

					if (j == strLength)
						return (m_Buffer + i);
				}
				return nullptr;
			}

			CONSTEXPR20 const char* Find(const std::string& string) const
			{
				return Find(string.data());
			}

			CONSTEXPR20 const char* Find(const String& string) const
			{
				return Find(string.m_Buffer);
			}

			/*
			*
			*	.Index method
			*
			*/

			CONSTEXPR20 size_t Index(const char character) const
			{
				for (size_t i{}; i < m_Length; ++i)
					if (m_Buffer[i] == character)
						return i;

				return m_Length;
			}

			CONSTEXPR20 size_t Index(const char* string) const
			{
				size_t strLength{ GetCStrLength(string) };

				if (m_Length < strLength)
					return m_Length;

				for (size_t i{}; i < m_Length; ++i)
				{
					size_t i_cpy{ i }, j{};
					while (j < strLength && m_Buffer[i_cpy] == string[j]) ++i_cpy, ++j;

					if (j == strLength)
						return i;
				}
				return m_Length;
			}

			CONSTEXPR20 size_t Index(const std::string& string) const
			{
				return Index(string.data());
			}

			CONSTEXPR20 size_t Index(const String& string) const
			{
				return Index(string.m_Buffer);
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

			CONSTEXPR20 unsigned int Count(const String& string) const
			{
				return Count(string.m_Buffer);
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
			*	.SubStr method
			*
			*/

			CONSTEXPR20 String SubStr(size_t startIndex, size_t endIndex) const
			{
				String buffer{ endIndex - startIndex };

				for (size_t i{ startIndex }; i < endIndex; ++i)
					buffer.append({ m_Buffer[i], '\0' });

				return buffer;
			}

			/*
			*
			*	.StartsWith method
			*
			*/

			CONSTEXPR20 const size_t StartsWith(const char character) const
			{
				return m_Buffer[0] == character;
			}

			CONSTEXPR20 const size_t StartsWith(const char* string) const
			{
				size_t strLength{ GetCStrLength(string) };

				if (strLength > m_Length)
					return false;

				for (size_t i{}; i < strLength; ++i)
					if (m_Buffer[i] != string[i])
						return false;

				return true;
			}

			CONSTEXPR20 const size_t StartsWith(const std::string& string) const
			{
				return StartsWith(string.data());
			}

			CONSTEXPR20 const size_t StartsWith(const String& string) const
			{
				return StartsWith(string.m_Buffer);
			}

			/*
			*
			*	.EndsWith method
			*
			*/

			CONSTEXPR20 const size_t EndsWith(const char character) const
			{
				return m_Buffer[m_Length - 1] == character;
			}

			CONSTEXPR20 const size_t EndsWith(const char* string) const
			{
				size_t strLength{ GetCStrLength(string) };

				if (strLength > m_Length)
					return false;

				size_t j{ strLength - 1 };
				size_t startFrom{ m_Length - 1 };

				for (; j > 0; --startFrom, --j)
					if (m_Buffer[startFrom] != string[j])
						return false;

				return (m_Buffer[startFrom] == string[j]);
			}

			CONSTEXPR20 const size_t EndsWith(const std::string& string) const
			{
				return EndsWith(string.data());
			}

			CONSTEXPR20 const size_t EndsWith(const String& string) const
			{
				return EndsWith(string.m_Buffer);
			}

			/*
			*
			*	.Format method
			*
			*/
			template<typename T, typename... TArgs>
			CONSTEXPR20 void formatter(String& data, const T& value)
			{
				size_t openBracket{ Index('{') };

				if (openBracket != m_Length)
				{
					size_t closeBracket{ Index('}') };

					if (closeBracket == m_Length)
					{
						throw std::runtime_error("Missing closing bracket!");
						return;
					}

					data.append(this->SubStr(0, openBracket));
					data.append(value);
					this->operator=(this->SubStr(closeBracket + 1, m_Length));
				}
			}

			template<typename... TArgs>
			CONSTEXPR20 String Format(TArgs... args)
			{
				String newStr;
				(formatter(newStr, args),...);
				newStr.append(this->Data());
				return newStr;
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

			CONSTEXPR20 const char operator[](size_t index) const
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

			NODISCARD17 CONSTEXPR20 String operator+(const char character) const
			{
				String newStr{ m_Buffer, (m_Length + sizeof(char) + 1) * sizeof(char) };
				newStr.append({ character, '\0' });

				return newStr;
			}

			NODISCARD17 CONSTEXPR20 String operator+(const char* string) const
			{
				String newStr{ m_Buffer, (m_Length + GetCStrLength(string) + 1) * sizeof(char) };
				newStr.append(string);

				return newStr;
			}

			NODISCARD17 CONSTEXPR20 String operator+(const std::string& string) const
			{
				return (*this + string.data());
			}

			NODISCARD17 CONSTEXPR20 String operator+(const String& string) const
			{
				return (*this + string.m_Buffer);
			}

			/*
			*
			*	operator*(string)
			*
			*/

			NODISCARD17 CONSTEXPR20 String operator*(size_t count) const
			{
				if (m_Length == 0)
					return String();

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
				size_t strSize{ (strLength + 1) * sizeof(char) };

				if (strSize > m_Size)
				{
					size_t sizeToAlloc{ strSize * 2 - 1 };
					DeallocStr(m_Buffer);
					AllocStr(m_Buffer, sizeToAlloc, false);

					if (m_Buffer)
					{
						m_Size = sizeToAlloc;
					}
					else
					{
						m_Length = 0;
						m_Size = 0;
						throw std::bad_alloc();
						return;
					}
				}

				m_Length = strLength;
				FillWString(m_Buffer, 0, m_Length, string);
				m_Buffer[m_Length] = '\0';
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
					FillWString(currentStr, 0, m_Length, m_Buffer);
					currentStr[m_Length] = '\0';
				}
				else
				{
					throw std::bad_alloc();
					return;
				}

				this->reserve((m_Size - 1) * count + 1);

				while (--count > 0)
					this->append(currentStr);

				DeallocStr(currentStr);
			}

			/*
			*
			*	operator==()
			*
			*/

			CONSTEXPR20 bool operator==(const char* string) const
			{
				if (m_Length != GetCStrLength(string)) return false;

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
	};
};

std::ostream& operator<<(std::ostream& stream, const CTL::Dynamic::String& data);

NODISCARD17 CONSTEXPR20 CTL::Dynamic::String operator""_DS(const char* string, size_t strLength)
{
	return CTL::Dynamic::String{ string, (strLength + 1) * sizeof(char) };
}