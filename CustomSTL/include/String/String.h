#pragma once

#include "CTL.h"

#include <iostream>
#include <type_traits>

#ifndef _MSVC_LANG
#error _MSVC_LANG macro is required, please refer to https://docs.microsoft.com/en-us/cpp/preprocessor/predefined-macros?view=msvc-170
#endif

// if C++14 or earlier is being used.
#if _MSVC_LANG < 201703L
#error C++17 or later is required for CTL to function!
#endif

_CTLBEGIN

// Foward Decl
class String;

// GetStrLen functions Decls
CONSTEXPR20 size_t GetStrLen(const char* str);
CONSTEXPR20 size_t GetStrLen(const std::string& str);
CONSTEXPR20 size_t GetStrLen(const String& str);

_DYNAMICBEGIN

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
		AllocInit(char, m_Buffer, 15);
	}

	/*
	*
	*	EXPLICIT CONSTRUCTORS
	*
	*/

	CONSTEXPR20 explicit String(const size_t length) : m_Length(0), m_Size(sizeof(char)* (length + 1))
	{
		AllocInit(char, m_Buffer, length + 1);
	}

	CONSTEXPR20 explicit String(const char* string, const size_t size = 0)
	{
		m_Length = GetStrLen(string);
		size_t stringSize{ (m_Length + 1) * sizeof(char) };
		m_Size = (size > 0) ? size : stringSize;

		if (m_Size < stringSize)
		{
			m_Length = 0;
			m_Size = 0;
			throw std::bad_array_new_length();
		}
		else
		{
			Alloc(char, m_Buffer, m_Size);
			FillWIterable(m_Buffer, 0, m_Length, string);
			m_Buffer[m_Length] = '\0';
		}
	}

	CONSTEXPR20 explicit String(const std::string& string) : m_Length(string.size()), m_Size((m_Length + 1) * sizeof(char))
	{
		Alloc(char, m_Buffer, m_Size);
		FillWIterable(m_Buffer, 0, m_Length, string);
		m_Buffer[m_Length] = '\0';
	}

	/*
	*
	*	COPY CONSTRUCTOR
	*
	*/

	CONSTEXPR20 String(const String& string) : m_Length(string.m_Length), m_Size(string.m_Size)
	{
		Alloc(m_Buffer, m_Size, false);

		if (m_Buffer)
		{
			FillWIterable(m_Buffer, 0, m_Length, string);
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
		Alloc(string.m_Buffer, 15 * sizeof(char), true);
		string.m_Length = 0;
	}

	/*
	*
	*	.Reserve method
	*
	*/

	CONSTEXPR20 void Reserve(const size_t size)
	{
		if (size <= m_Size)
			return;

		if (m_Length == 0)
		{
			Dealloc(m_Buffer);
			Alloc(m_Buffer, size, true);

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
			Alloc(m_Buffer, size, false);

			if (m_Buffer)
			{
				FillWIterable(m_Buffer, 0, m_Length, oldStr);
				m_Buffer[m_Length] = '\0';
				m_Size = size;
				Dealloc(oldStr);
			}
			else
			{
				m_Length = 0;
				m_Size = 0;
				Dealloc(oldStr);
				throw std::bad_alloc();
			}
		}
	}

	/*
	*
	*	.Append method
	*
	*/

	CONSTEXPR20 void Append(const char character)
	{
		if ((++m_Length * sizeof(char)) >= m_Size)
		{
			char* oldStr{ m_Buffer };

			m_Size *= 2;
			Alloc(m_Buffer, m_Size, false);

			if (m_Buffer)
			{
				for (size_t i{}; i < m_Length - 1; ++i)
					m_Buffer[i] = oldStr[i];

				m_Buffer[m_Length - 1] = character;
				m_Buffer[m_Length] = '\0';

				Dealloc(oldStr);
			}
			else
			{
				Dealloc(oldStr);

				m_Length = 0;
				m_Size = 0;

				throw std::bad_alloc();
			}
		}
		else
		{
			m_Buffer[m_Length - 1] = character;
			m_Buffer[m_Length] = '\0';
		}
	}

	CONSTEXPR20 void Append(const char* string)
	{
		size_t strLength{ GetStrLen(string) };
		size_t strSize{ (m_Length + strLength + 1) * sizeof(char) };

		if (m_Size < strSize)
		{

			if (m_Length == 0)
			{
				Dealloc(m_Buffer);
				Alloc(m_Buffer, strSize, false);

				if (m_Buffer)
				{
					FillWIterable(m_Buffer, 0, strLength, string);
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

				Alloc(m_Buffer, newStrSize, false);
				if (m_Buffer)
				{
					FillWIterable(m_Buffer, 0, m_Length, oldStr);

					size_t i{ m_Length };
					size_t j{};

					m_Length += strLength;
					for (; i < m_Length; ++j, ++i)
						m_Buffer[i] = string[j];
					m_Buffer[m_Length] = '\0';

					m_Size = newStrSize;
					Dealloc(oldStr);
				}
				else
				{
					Dealloc(oldStr);
					throw std::bad_alloc();
				}
			}
		}
		else
		{
			size_t i{ m_Length };
			size_t j{};

			m_Length += strLength;
			for (; i < m_Length; ++j, ++i)
				m_Buffer[i] = string[j];
			m_Buffer[m_Length] = '\0';
		}
	}

	CONSTEXPR20 void Append(const std::string& string)
	{
		Append(string.data());
	}

	CONSTEXPR20 void Append(const String& string)
	{
		Append(string.m_Buffer);
	}

	/*
	* 
	*	AppendAll
	* 
	*/

	template<typename... Strings>
	CONSTEXPR20 void AppendAll(const Strings&... VarStrings)
	{
		static_assert
		(
			(std::is_same_v<Strings, char*>||...) ||
			(std::is_same_v<Strings, std::string>||...) ||
			(std::is_same_v<Strings, String>||...),
			"AppendAll only accepts (char*, std::string, and CTL::Dynamic::String)!"
		);

		Reserve(((GetStrLen(VarStrings) + ...) + (m_Length + 1)) * sizeof(char));
		(Append(VarStrings),...);
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
		size_t strLength{ GetStrLen(string) };

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
		size_t strLength{ GetStrLen(string) };

		if (m_Length < strLength)
			return (m_Buffer + m_Length);

		for (size_t i{}; i < m_Length; ++i)
		{
			size_t i_cpy{ i }, j{};
			while (j < strLength && m_Buffer[i_cpy] == string[j]) ++i_cpy, ++j;

			if (j == strLength)
				return (m_Buffer + i);
		}
		return (m_Buffer + m_Length);
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
		size_t strLength{ GetStrLen(string) };

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

	CONSTEXPR20 size_t Index(const char character, unsigned int occurrenceNumber = 1u) const
	{
		for (size_t i{}; i < m_Length; ++i)
			if (m_Buffer[i] == character && --occurrenceNumber == 0u)
				return i;

		return m_Length;
	}

	CONSTEXPR20 size_t Index(const char* string, unsigned int occurrenceNumber = 1u) const
	{
		size_t strLength{ GetStrLen(string) };

		if (m_Length < strLength)
			return m_Length;

		for (size_t i{}; i < m_Length; ++i)
		{
			size_t i_cpy{ i }, j{};
			while (j < strLength && m_Buffer[i_cpy] == string[j]) ++i_cpy, ++j;

			if (j == strLength && --occurrenceNumber == 0u)
				return i;
		}
		return m_Length;
	}

	CONSTEXPR20 size_t Index(const std::string& string, unsigned int occurrenceNumber = 1u) const
	{
		return Index(string.data(), occurrenceNumber);
	}

	CONSTEXPR20 size_t Index(const String& string, unsigned int occurrenceNumber = 1u) const
	{
		return Index(string.m_Buffer, occurrenceNumber);
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
		size_t strLength{ GetStrLen(string) };

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
		if (endIndex > m_Length)
			return {};

		String data(endIndex - startIndex);
		data.Append((m_Buffer + startIndex));
		data.m_Buffer[endIndex - startIndex] = '\0';

		return data;
	}

	CONSTEXPR20 String SubStrC(size_t startIndex, size_t count) const
	{
		if (count > GetStrLen(m_Buffer + startIndex))
			return {};

		String resultStr{ count };
				
		for (size_t i{ startIndex }; i < (startIndex + count); ++i)
			resultStr.Append(m_Buffer[i]);

		return resultStr;
	}

	/*
	*
	*	.StartsWith method
	*
	*/

	CONSTEXPR20 const bool StartsWith(const char character) const
	{
		return m_Buffer[0] == character;
	}

	CONSTEXPR20 const bool StartsWith(const char* string) const
	{
		size_t strLength{ GetStrLen(string) };

		if (strLength > m_Length)
			return false;

		for (size_t i{}; i < strLength; ++i)
			if (m_Buffer[i] != string[i])
				return false;

		return true;
	}

	CONSTEXPR20 const bool StartsWith(const std::string& string) const
	{
		return StartsWith(string.data());
	}

	CONSTEXPR20 const bool StartsWith(const String& string) const
	{
		return StartsWith(string.m_Buffer);
	}

	/*
	*
	*	.EndsWith method
	*
	*/

	CONSTEXPR20 const bool EndsWith(const char character) const
	{
		return m_Buffer[m_Length - 1] == character;
	}

	CONSTEXPR20 const bool EndsWith(const char* string) const
	{
		size_t strLength{ GetStrLen(string) };

		if (strLength > m_Length)
			return false;

		size_t j{ strLength - 1 };
		size_t startFrom{ m_Length - 1 };

		for (; j > 0; --startFrom, --j)
			if (m_Buffer[startFrom] != string[j])
				return false;

		return (m_Buffer[startFrom] == string[j]);
	}

	CONSTEXPR20 const bool EndsWith(const std::string& string) const
	{
		return EndsWith(string.data());
	}

	CONSTEXPR20 const bool EndsWith(const String& string) const
	{
		return EndsWith(string.m_Buffer);
	}

	/*
	*
	*	.Format method
	*
	*/

	template<typename... TArgs>
	CONSTEXPR20 String Format(TArgs... args)
	{
		String resultStr;
		size_t bracketCount{ 1 };
		size_t nextStartingPoint{};

		(formatter(resultStr, args, bracketCount, nextStartingPoint),...);
		resultStr.Append(m_Buffer + Index('}', bracketCount - 1) + 1);
		return resultStr;
	}

	/*
	*
	*	.IsSomething methods
	*
	*/

	CONSTEXPR20 bool IsAlnum() const
	{
		if (m_Length == 0)
			return false;

		for (size_t i{}; i < m_Length; ++i)
		{
			int characterAsInt{ m_Buffer[i] };

			if (!((47 < characterAsInt && characterAsInt < 58) || (64 < characterAsInt && characterAsInt < 91) || (96 < characterAsInt && characterAsInt < 123)))
				return false;
		}

		return true;
	}

	CONSTEXPR20 bool IsAlpha() const
	{
		if (m_Length == 0)
			return false;

		for (size_t i{}; i < m_Length; ++i)
		{
			int characterAsInt{ m_Buffer[i] };

			if (!((64 < characterAsInt && characterAsInt < 91) || (96 < characterAsInt && characterAsInt < 123)))
				return false;
		}

		return true;
	}

	CONSTEXPR20 bool IsDigit() const
	{
		if (m_Length == 0)
			return false;

		for (size_t i{}; i < m_Length; ++i)
		{
			int characterAsInt{ m_Buffer[i] };

			if (!(47 < characterAsInt && characterAsInt < 58))
				return false;
		}

		return true;
	}

	CONSTEXPR20 bool IsLower() const
	{
		if (m_Length == 0)
			return false;

		for (size_t i{}; i < m_Length; ++i)
		{
			int characterAsInt{ m_Buffer[i] };

			if (!(96 < characterAsInt && characterAsInt < 123))
				return false;
		}

		return true;
	}

	CONSTEXPR20 bool IsUpper() const
	{
		if (m_Length == 0)
			return false;

		for (size_t i{}; i < m_Length; ++i)
		{
			int characterAsInt{ m_Buffer[i] };

			if (!(64 < characterAsInt && characterAsInt < 91))
				return false;
		}

		return true;
	}

	CONSTEXPR20 bool IsTitle(bool ignoreNumbers = true) const
	{
		if (m_Length == 0)
			return false;

		if (ignoreNumbers)
		{
			bool characterFound{ false };

			for (size_t i{}, lastSpaceOccurrenceIndex{}; i < m_Length; ++lastSpaceOccurrenceIndex, i = Index(' ', lastSpaceOccurrenceIndex) + 1)
			{
				if (!(64 < m_Buffer[i] && m_Buffer[i] < 91))
				{
					if (!(47 < m_Buffer[i] && m_Buffer[i] < 58))
						return false;
				}
				else
					characterFound = true;
			}

			return characterFound;
		}
\
		for (size_t i{}, lastSpaceOccurrenceIndex{}; i < m_Length; ++lastSpaceOccurrenceIndex, i = Index(' ', lastSpaceOccurrenceIndex) + 1)
		{
			if (!(64 < m_Buffer[i] && m_Buffer[i] < 91))
				return false;
		}

		return true;
	}

	/*
	*
	*	.Upper/Lower methods
	*
	*/

	CONSTEXPR20 String& ToUpper()
	{
		for (size_t i{}; i < m_Length; ++i)
		{
			int characterAsInt{ m_Buffer[i] };

			if (96 < characterAsInt && characterAsInt < 123)
				m_Buffer[i] -= 32;
		}

		return *this;
	}

	CONSTEXPR20 String Upper() const
	{
		String upperStr{ *this };

		for (size_t i{}; i < m_Length; ++i)
		{
			int characterAsInt{ upperStr[i] };

			if (96 < characterAsInt && characterAsInt < 123)
				upperStr[i] -= 32;
		}

		return upperStr;
	}

	CONSTEXPR20 String& ToLower()
	{
		for (size_t i{}; i < m_Length; ++i)
		{
			int characterAsInt{ m_Buffer[i] };

			if (64 < characterAsInt && characterAsInt < 91)
				m_Buffer[i] += 32;
		}

		return *this;
	}

	CONSTEXPR20 String Lower() const
	{
		String lowerStr{ *this };

		for (size_t i{}; i < m_Length; ++i)
		{
			int characterAsInt{ lowerStr[i] };

			if (64 < characterAsInt && characterAsInt < 91)
				lowerStr[i] += 32;
		}

		return lowerStr;
	}

	/*
	*
	*	.Capitalize method
	*
	*/

	CONSTEXPR20 String& Capitalize()
	{
		if (m_Length == 0)
			return *this;

		int characterAsInt{ m_Buffer[0] };

		if (96 < characterAsInt && characterAsInt < 123)
			m_Buffer[0] -= 32;

		return *this;
	}

	/*
	*
	*	.Title method
	*
	*/

	CONSTEXPR20 String& Title()
	{
		if (m_Length == 0)
			return *this;

		int characterAsInt{ m_Buffer[0] };

		if (96 < characterAsInt && characterAsInt < 123)
			m_Buffer[0] -= 32;

		for (size_t i{}; i < m_Length; ++i)
		{
			characterAsInt = m_Buffer[i];

			if (characterAsInt == 32 || characterAsInt == 9 || characterAsInt == 10)
			{
				characterAsInt = m_Buffer[i + 1];

				if (96 < characterAsInt && characterAsInt < 123)
					m_Buffer[++i] -= 32;
			}
		}

		return *this;
	}

	/*
	*
	*	.Swap method
	*
	*/

	CONSTEXPR20 void Swap(String& other)
	{
		String temp{ std::move(other) };
		other = std::move(*this);
		*this = std::move(temp);
	}

	/*
	*
	*	.Shrinking methods
	*
	*/
			
	CONSTEXPR20 void ShrinkToFit()
	{
		if ((m_Size / sizeof(char) - 1) == m_Length)
			return;

		char* data{ m_Buffer };
		size_t newSize{ (m_Length + 1) * sizeof(char) };
				
		Alloc(m_Buffer, newSize, false);

		if (m_Buffer)
		{
			m_Size = newSize;
			for (size_t i{}; i < m_Length; ++i)
				m_Buffer[i] = data[i];

			m_Buffer[m_Length] = '\0';

			Dealloc(data);
		}
		else
			m_Buffer = data;
	}

	CONSTEXPR20 void Shrink(size_t newSize)
	{
		if (newSize < ((m_Length + 1) * sizeof(char)))
			return;

		char* data{ m_Buffer };
		Alloc(m_Buffer, newSize, false);

		if (m_Buffer)
		{
			m_Size = newSize;
			for (size_t i{}; i < m_Length; ++i)
				m_Buffer[i] = data[i];

			m_Buffer[m_Length] = '\0';

			Dealloc(data);
		}
		else
			m_Buffer = data;
	}

	/*
	*
	*	.Replace method
	*
	*/

	CONSTEXPR20 void InPlaceReplace(char charA, char charB)
	{
		char* charPos{ Find(charA) };

		if (charPos)
			charPos[0] = charB;
	}

	template<typename T, typename H>
	CONSTEXPR20 void InPlaceReplace(const T& toFindStr, const H& toReplStr)
	{
		static_assert(
			(std::is_array_v<T> || std::is_same_v<T, const char*> || std::is_same_v<T, std::string> || std::is_same_v<T, String>) &&
			(std::is_array_v<H> || std::is_same_v<H, const char*> || std::is_same_v<H, std::string> || std::is_same_v<H, String>),
			"This method only accepts any of (const char*, std::string, or CTL::Dynamic::String) types."
		);

		if (&toReplStr == this)
			throw std::logic_error("Cannot replace with same object (conflicts detected!)");

		size_t toFindStrLen{ GetStrLen(toFindStr) };
		size_t toReplStrLen{ GetStrLen(toReplStr) };

		size_t stringPos{ Index(toFindStr) };

		if (stringPos == m_Length)
			return;

		if (toFindStrLen == toReplStrLen)
		{
			for (size_t i{ stringPos }, j{}; i < (stringPos + toFindStrLen); ++j, ++i)
				m_Buffer[i] = toReplStr[j];

			return;
		}

		char* tempHolder{ m_Buffer };

		if (toFindStrLen > toReplStrLen)
		{
			replacer(m_Buffer, tempHolder, toReplStr, stringPos, toFindStrLen, toReplStrLen);
			m_Length -= (toFindStrLen - toReplStrLen);
			return;
		}

		size_t newLen{ m_Length + toReplStrLen - toFindStrLen };
		m_Size = (newLen + 1) * sizeof(char);
		Alloc(m_Buffer, m_Size, false);

		if (m_Buffer)
		{
			size_t i{};
			while (i < stringPos)
			{
				m_Buffer[i] = tempHolder[i];
				++i;
			}

			replacer(m_Buffer, tempHolder, toReplStr, i, toFindStrLen, toReplStrLen);

			m_Length = newLen;
			m_Buffer[m_Length] = '\0';

			Dealloc(tempHolder);
		}
		else
		{
			Dealloc(tempHolder);
			m_Length = 0;
			m_Size = 0;

			throw std::bad_alloc();
		}
	}

	template<typename T, typename H>
	CONSTEXPR20 String Replace(const T& toFindStr, const H& toReplStr)
	{
		// review this method.

		static_assert(
			(std::is_array_v<T> || std::is_same_v<T, const char*> || std::is_same_v<T, std::string> || std::is_same_v<T, String>) &&
			(std::is_array_v<H> || std::is_same_v<H, const char*> || std::is_same_v<H, std::string> || std::is_same_v<H, String>),
			"This method only accepts any of (const char*, std::string, or CTL::Dynamic::String) types."
			);

		size_t toFindStrLen{ GetStrLen(toFindStr) };
		size_t toReplStrLen{ GetStrLen(toReplStr) };

		size_t stringPos{ Index(toFindStr) };

		String resultStr{ m_Length + toReplStrLen - toFindStrLen + 1 };
		resultStr.m_Length = m_Length + toReplStrLen - toFindStrLen + 1;

		size_t i{};
		for (; i < stringPos; ++i)
			resultStr[i] = m_Buffer[i];

		for (size_t j{}; j < toReplStrLen; ++i, ++j)
			resultStr[i] = toReplStr[j];

		for (size_t j{ stringPos + toFindStrLen }; j < m_Length; ++i, ++j)
			resultStr[i] = m_Buffer[j];

		std::cout << resultStr[i] << '\n';
		return resultStr;
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
		newStr.Append(character);

		return newStr;
	}

	NODISCARD17 CONSTEXPR20 String operator+(const char* string) const
	{
		String newStr{ m_Buffer, (m_Length + GetStrLen(string) + 1) * sizeof(char) };
		newStr.Append(string);

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
			newStr.Append(thisStr);

		return newStr;
	}

	/*
	*
	*	operator=(string)
	*
	*/

	CONSTEXPR20 String& operator=(const char* string)
	{
		size_t strLength{ GetStrLen(string) };
		size_t strSize{ (strLength + 1) * sizeof(char) };

		if (strSize > m_Size)
		{
			size_t sizeToAlloc{ strSize * 2 - 1 };
			Dealloc(m_Buffer);
			Alloc(m_Buffer, sizeToAlloc, false);

			if (m_Buffer)
			{
				m_Size = sizeToAlloc;
			}
			else
			{
				m_Length = 0;
				m_Size = 0;
				throw std::bad_alloc();
				return *this;
			}
		}

		m_Length = strLength;
		FillWIterable(m_Buffer, 0, m_Length, string);
		m_Buffer[m_Length] = '\0';

		return *this;
	}

	CONSTEXPR20 String& operator=(const std::string& string)
	{
		return this->operator=(string.data());
	}

	CONSTEXPR20 String& operator=(const String& string)
	{
		return this->operator=(string.m_Buffer);
	}

	CONSTEXPR20 String& operator=(String&& other) noexcept
	{
		m_Buffer = other.m_Buffer;
		m_Length = other.m_Length;
		m_Size = other.m_Size;

		other.m_Size = 15 * sizeof(char);
		Alloc(other.m_Buffer, other.m_Size, true);
		other.m_Length = 0;

		return *this;
	}

	/*
	*
	*	operator+=(string)
	*
	*/

	CONSTEXPR20 void operator+=(const char character)
	{
		this->Append(character);
	}

	CONSTEXPR20 void operator+=(const char* string)
	{
		this->Append(string);
	}

	CONSTEXPR20 void operator+=(const std::string& string)
	{
		return this->Append(string.data());
	}

	CONSTEXPR20 void operator+=(const String& string)
	{
		return this->Append(string.m_Buffer);
	}

	/*
	*
	*	operator*=()
	*
	*/
	CONSTEXPR20 void operator*=(size_t count)
	{
		char* currentStr;
		Alloc(currentStr, m_Size, false);

		if (currentStr)
		{
			FillWIterable(currentStr, 0, m_Length, m_Buffer);
			currentStr[m_Length] = '\0';
		}
		else
		{
			throw std::bad_alloc();
			return;
		}

		this->Reserve((m_Size - 1) * count + 1);

		while (--count > 0)
			this->Append(currentStr);

		Dealloc(currentStr);
	}

	/*
	*
	*	operator==()
	*
	*/

	CONSTEXPR20 bool operator==(const char* string) const
	{
		if (m_Length != GetStrLen(string)) return false;

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
		Dealloc(m_Buffer);
	}

	/*
	*
	*	operator std::string()
	*
	*/

	operator std::string()
	{
		return std::string{ m_Buffer };
	}

private:
	template<typename T>
	CONSTEXPR20 void formatter(String& resultStr, const T& value, size_t& bracketCount, size_t& nextStartingPoint)
	{
		size_t openBracket{ Index('{', bracketCount) };

		if (openBracket != m_Length)
		{
			size_t closeBracket{ Index('}', bracketCount) };

			if (closeBracket == m_Length)
			{
				throw std::runtime_error("Missing closing bracket!");
				return;
			}

			resultStr.Append(this->SubStr(nextStartingPoint, openBracket));
			resultStr.Append(value);

			nextStartingPoint = closeBracket + 1;
			++bracketCount;
		}
	}

	template<typename T, typename H>
	CONSTEXPR20 void replacer(T& m_Buffer, T& tempHolder, H& toReplStr, size_t i, size_t toFindStrLen, size_t toReplStrLen)
	{
		size_t stringPos{ i };

		for (size_t j{}; j < toReplStrLen; ++i, ++j)
			m_Buffer[i] = toReplStr[j];

		size_t h{ stringPos + toFindStrLen };
		while (h < (m_Length + 1))
		{
			m_Buffer[i] = tempHolder[h];
			++h, ++i;
		}
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

__forceinline std::ostream& operator<<(std::ostream& stream, const String& data)
{
	return stream << data.Data();
}

_DYNAMICEND

/*
*
*	length functions
*
*/

CONSTEXPR20 size_t GetStrLen(const char* str)
{
	size_t i{};
	while (str[i++] != '\0');

	return i - 1;
}

CONSTEXPR20 size_t GetStrLen(const std::string& str)
{
	return str.length();
}

CONSTEXPR20 size_t GetStrLen(const Dynamic::String& str)
{
	return str.Length();
}

_CTLEND

NODISCARD17 CONSTEXPR20 CTL::Dynamic::String operator""_DS(const char* string, size_t strLength)
{
	return CTL::Dynamic::String{ string };
}