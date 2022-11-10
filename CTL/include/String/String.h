#pragma once

#include "CTL.h"
#include <iostream>

// Foward Decl
_CTLBEGIN
_DYNAMICBEGIN
class String;
_DYNAMICEND
_CTLEND

// GetStrLen functions Decls
template<typename T>
constexpr size_t GetStrLen(const T str);
constexpr size_t GetStrLen(char* str);
constexpr size_t GetStrLen(const char* str);
CONSTEXPR20 size_t GetStrLen(const std::string& str);
CONSTEXPR20 size_t GetStrLen(const CTL::Dynamic::String & str);

class CTL::Dynamic::String
{
public:

	/*
	*
	*	CONSTRUCTORS
	*
	*/

	// IMPLICIT
	CONSTEXPR20 String() : m_Length(0), m_Size(sizeof(char) * 15)
	{
		AllocIterableInit(char, m_Buffer, 15);
	}

	// EXPLICIT
	CONSTEXPR20 explicit String(const size_t length) : m_Length(0), m_Size(sizeof(char)* (length + 1))
	{
		AllocIterableInit(char, m_Buffer, length);
	}

	CONSTEXPR20 explicit String(const char* string)
	{
		m_Length = GetStrLen(string);
		m_Size = (m_Length + 1) * sizeof(char);

		AllocIterable(char, m_Buffer, m_Length);
		CopyIterable(m_Buffer, 0, m_Length, string);
		m_Buffer[m_Length] = '\0';
	}

	CONSTEXPR20 explicit String(const char* string, const size_t length)
	{
		const size_t strLen{ GetStrLen(string) };

		m_Length = (length >= strLen) ? length : strLen;
		m_Size = (m_Length + 1) * sizeof(char);
		AllocIterable(char, m_Buffer, m_Length);
		CopyIterable(m_Buffer, 0, m_Length, string);
		m_Buffer[m_Length] = '\0';
	}

	CONSTEXPR20 explicit String(const std::string& string) : m_Length(string.length()), m_Size((m_Length + 1) * sizeof(char))
	{
		AllocIterable(char, m_Buffer, m_Length);
		CopyIterable(m_Buffer, 0, m_Length, string);
		m_Buffer[m_Length] = '\0';
	}

	// COPY
	CONSTEXPR20 String(const String& string) : m_Length(string.m_Length), m_Size(string.m_Size)
	{
		AllocIterable(char, m_Buffer, m_Length);
		CopyIterable(m_Buffer, 0, m_Length, string.m_Buffer);
		m_Buffer[m_Length] = '\0';
	}

	// MOVE
	CONSTEXPR20 String(String&& string) noexcept : m_Length(string.m_Length), m_Size(string.m_Size), m_Buffer(string.m_Buffer)
	{
		string.m_Size = 15 * sizeof(char);
		AllocIterableInit(char, string.m_Buffer, 15);
		string.m_Length = 0;
	}

	/*
	*
	*	.Methods()
	*
	*/

	// .Append()
	CONSTEXPR20 void Append(const char character)
	{
		if (IsFilled())
		{
			m_Size = m_Size * 2 - sizeof(char);
			ReAllocIterable(char, m_Buffer, m_Length, (m_Length * 2));
		}

		m_Buffer[m_Length] = character;
		m_Buffer[++m_Length] = '\0';
	}

	template<typename T>
	CONSTEXPR20 void Append(const T& string)
	{
		static_assert(
			IsAnyOf<T, char*, const char*, std::string, CTL::Dynamic::String>::value || (std::is_same_v<std::remove_all_extents_t<T>, char> && std::is_array_v<T>),
			"Append only accepts (char*, const char*, char[], std::string, and CTL::Dynamic::String)!"
			);

		size_t strLength{ GetStrLen(string) };
		size_t newLen{ m_Length + strLength };
		size_t combinedStrSize{ (newLen + 1) * sizeof(char) };

		if (m_Size < combinedStrSize)
		{
			m_Size = combinedStrSize * 2 - sizeof(char);
			ReAllocIterable(char, m_Buffer, m_Length, (newLen * 2));
		}

		char* tempBuffer{ m_Buffer + m_Length };
		CopyIterable(tempBuffer, 0, strLength, string);
		tempBuffer[strLength] = '\0';
		m_Length = newLen;
	}

	// .AppendAll()
	template<typename... Strings>
	CONSTEXPR20 void AppendAll(const Strings&... VarStrings)
	{
		static_assert(
			((IsAnyOf<Strings, char*, const char*, std::string, CTL::Dynamic::String>::value || (std::is_same_v<std::remove_all_extents_t<Strings>, char> && std::is_array_v<Strings>))&&...),
			"AppendAll only accepts (char*, const char*, std::string, and CTL::Dynamic::String)!"
			);
		Reserve(((GetStrLen(VarStrings) + ...) + m_Length + 1) * sizeof(char) * 2);
		(Append(VarStrings), ...);
	}

	// .Capitalize()
	CONSTEXPR20 String& Capitalize()
	{
		if (m_Length == 0)
			return *this;

		int characterAsInt{ *m_Buffer };

		if (IsLowerChar(characterAsInt))
			*m_Buffer -= 32;

		return *this;
	}

	// .Count()
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

	// .EndsWith
	CONSTEXPR20 const bool EndsWith(const char character) const
	{
		return m_Buffer[m_Length - 1] == character;
	}

	CONSTEXPR20 const bool EndsWith(const char* string) const
	{
		size_t strLength{ GetStrLen(string) };

		if (strLength > m_Length)
			return false;

		for (size_t i{ m_Length - strLength }, j{}; j < strLength; ++i, ++j)
			if (m_Buffer[i] != string[j])
				return false;

		return true;
	}

	CONSTEXPR20 const bool EndsWith(const std::string& string) const
	{
		return EndsWith(string.data());
	}

	CONSTEXPR20 const bool EndsWith(const String& string) const
	{
		return EndsWith(string.m_Buffer);
	}

	// .Find()

	// non-const
	CONSTEXPR20 char* Find(const char character, unsigned int occurrenceNumber = 1u)
	{
		return m_Buffer + Index(character, occurrenceNumber);
	}

	CONSTEXPR20 char* Find(const char* string, unsigned int occurrenceNumber = 1u)
	{
		return m_Buffer + Index(string, occurrenceNumber);
	}

	CONSTEXPR20 char* Find(const std::string& string, unsigned int occurrenceNumber = 1u)
	{
		return m_Buffer + Index(string.data(), occurrenceNumber);
	}

	CONSTEXPR20 char* Find(const String& string, unsigned int occurrenceNumber = 1u)
	{
		return m_Buffer + Index(string.m_Buffer, occurrenceNumber);
	}

	// const
	CONSTEXPR20 const char* Find(const char character, unsigned int occurrenceNumber = 1u) const
	{
		return m_Buffer + Index(character, occurrenceNumber);
	}

	CONSTEXPR20 const char* Find(const char* string, unsigned int occurrenceNumber = 1u) const
	{
		return m_Buffer + Index(string, occurrenceNumber);
	}

	CONSTEXPR20 const char* Find(const std::string& string, unsigned int occurrenceNumber = 1u) const
	{
		return m_Buffer + Index(string.data(), occurrenceNumber);
	}

	CONSTEXPR20 const char* Find(const String& string, unsigned int occurrenceNumber = 1u) const
	{
		return m_Buffer + Index(string.Data(), occurrenceNumber);
	}

	// .Format()
	template<typename... TArgs>
	CONSTEXPR20 String Format(TArgs... args)
	{
		String resultStr;
		size_t nextStartingPoint{}, bracketCount{ 1 };

		(formatter(resultStr, args, bracketCount, nextStartingPoint), ...);
		resultStr.Append(m_Buffer + nextStartingPoint);

		return resultStr;
	}

	// .Has()
	CONSTEXPR20 bool Has(const char character) const
	{
		return Index(character) != m_Length;
	}

	CONSTEXPR20 bool Has(const char* string) const
	{
		return Index(string) != m_Length;
	}

	CONSTEXPR20 bool Has(const std::string& string) const
	{
		return Index(string.data()) != m_Length;
	}

	CONSTEXPR20 bool Has(const String& string) const
	{
		return Index(string.m_Buffer) != m_Length;
	}

	// .Index()
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
			size_t j{};
			for (size_t i_cpy{ i }; j < strLength && m_Buffer[i_cpy] == string[j]; ++j, ++i_cpy);

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

	// .Insert()
	CONSTEXPR20 void Insert(const char character, const size_t index)
	{
		if (index > m_Length)
		{
			throw std::logic_error("index is out of bounds!");
			return;
		}

		++m_Length;
		Reserve(m_Length);
		ShiftToRight(m_Buffer, index, m_Length, 1);
		m_Buffer[index] = character;
	}

	CONSTEXPR20 void Insert(const char* string, const size_t index)
	{
		if (index > m_Length)
		{
			throw std::logic_error("index is out of bounds!");
			return;
		}

		size_t stringLen{ GetStrLen(string) };
		size_t bufferCount{ m_Length + 1 };
		Reserve(stringLen + m_Length);

		char* tempBuffer{ m_Buffer + index };

		ShiftToRight(m_Buffer, index, bufferCount, stringLen);
		CopyIterable(tempBuffer, 0, stringLen, string);
		m_Length += stringLen;
	}

	CONSTEXPR20 void Insert(const std::string& string, const size_t index)
	{
		Insert(string.data(), index);
	}

	CONSTEXPR20 void Insert(const String& string, const size_t index)
	{
		Insert(string.m_Buffer, index);
	}

	// .InPlaceReplace()
	CONSTEXPR20 void InPlaceReplace(char charA, char charB)
	{
		char* charPos{ Find(charA) };

		if (*charPos != '\0')
			charPos[0] = charB;
	}

	template<typename T, typename H>
	CONSTEXPR20 void InPlaceReplace(const T& toFindStr, const H& toReplStr)
	{
		static_assert(
			(std::is_array_v<T> || IsAnyOf<T, char*, const char*, std::string, String>::value) &&
			(std::is_array_v<H> || IsAnyOf<H, char*, const char*, std::string, String>::value),
			"This method only accepts any of (const char*, std::string, or CTL::Dynamic::String) types."
			);

		// code yet to be written.
	}

	// .IsSomething()
	CONSTEXPR20 bool IsFilled() const
	{
		return ((m_Length + 1) * sizeof(char)) == m_Size;
	}

	CONSTEXPR20 bool IsEmpty() const
	{
		return m_Length == 0;
	}

	CONSTEXPR20 bool IsAlnum() const
	{
		if (m_Length == 0)
			return false;

		for (size_t i{}; i < m_Length; ++i)
		{
			int characterAsInt{ m_Buffer[i] };

			if (!(IsNum(characterAsInt) || IsChar(characterAsInt)))
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

			if (!IsChar(characterAsInt))
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

			if (!IsNum(characterAsInt))
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

			if (!IsLowerChar(characterAsInt))
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

			if (!IsUpperChar(characterAsInt))
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
			for (size_t i{}, lastSpaceOccurrence{}; i < m_Length; ++lastSpaceOccurrence, i = Index(' ', lastSpaceOccurrence) + 1)
			{
				int characterAsInt{ m_Buffer[i] };

				if (!(IsUpperChar(characterAsInt) || IsNum(characterAsInt)))
					return false;
			}

			return true;
		}

		for (size_t i{}, lastSpaceOccurrence{}; i < m_Length; ++lastSpaceOccurrence, i = Index(' ', lastSpaceOccurrence) + 1)
		{
			int characterAsInt{ m_Buffer[i] };

			if (!IsUpperChar(characterAsInt))
				return false;
		}

		return true;
	}

	// .Lower()
	CONSTEXPR20 String Lower() const
	{
		return String{ *this }.ToLower();
	}

	// .Reserve()
	CONSTEXPR20 bool Reserve(const size_t length)
	{
		size_t newSize{ (length + 1) * sizeof(char) };

		if (newSize <= m_Size)
			return false;

		char* oldBuffer{ m_Buffer };

		try
		{
			AllocIterable(char, m_Buffer, length);
		}
		catch (const std::bad_alloc&)
		{
			m_Buffer = oldBuffer;
			return false;
		}

		CopyIterable(m_Buffer, 0, m_Length, oldBuffer);
		DeAlloc(oldBuffer);
		m_Buffer[m_Length] = '\0';
		m_Size = newSize;
		return true;
	}

	// .Reset()
	CONSTEXPR20 void ReAlloc() noexcept
	{
		m_Length = 0;
		m_Size = 15 * sizeof(char);
		AllocIterableInit(char, m_Buffer, 15);
	}

	CONSTEXPR20 void Reset() noexcept
	{
		DeAlloc(m_Buffer);
		m_Length = 0;
		m_Size = 15 * sizeof(char);
		AllocIterableInit(char, m_Buffer, 15);
	}

	// .Replace()
	template<typename T, typename H>
	CONSTEXPR20 String Replace(const T& toFindStr, const H& toReplStr)
	{
		static_assert(
			(std::is_array_v<T> || IsAnyOf<T, char*, const char*, std::string, String>::value) &&
			(std::is_array_v<H> || IsAnyOf<H, char*, const char*, std::string, String>::value),
			"This method only accepts any of (const char*, std::string, or CTL::Dynamic::String) types."
			);

		int toFindStrLen(GetStrLen(toFindStr));
		int toReplStrLen(GetStrLen(toReplStr));

		String resultStr{ m_Length + Count(toFindStr) * (toReplStrLen - toFindStrLen) };
		char* tempResultBuffer{ resultStr.m_Buffer };

		size_t end{ Index(toFindStr) };
		char* tempBuffer{ m_Buffer };

		for (size_t src{ end }, oldSrc{}, occurence{ 1 }; src != m_Length; ++occurence, oldSrc = src + toFindStrLen, src = Index(toFindStr, occurence), end = src - oldSrc, tempBuffer = m_Buffer + oldSrc)
		{
			CopyIterable(tempResultBuffer, 0, end, tempBuffer);

			tempResultBuffer += end;

			CopyIterable(tempResultBuffer, 0, toReplStrLen, toReplStr);

			tempResultBuffer += toReplStrLen;
		}

		CopyIterable(tempResultBuffer, 0, end, tempBuffer);

		return resultStr;
	}

	// .ReverseIndex()
	CONSTEXPR20 size_t ReverseIndex(const char character, unsigned int occurrenceNumber = 1u) const
	{
		size_t i{ m_Length };
		while (i > 0)
		{
			--i;
			if (m_Buffer[i] == character && --occurrenceNumber == 0u)
				return i;
		}

		return m_Length;
	}

	// .Shrink()
	CONSTEXPR20 bool Shrink(size_t length)
	{
		if (length >= m_Length)
			return false;

		char* data{ m_Buffer };

		try
		{
			AllocIterable(char, m_Buffer, length);
		}
		catch (std::bad_alloc)
		{
			m_Buffer = data;
			return false;
		}

		m_Length = length;
		m_Size = (m_Length + 1) * sizeof(char);

		CopyIterable(m_Buffer, 0, m_Length, data);
		m_Buffer[m_Length] = '\0';
		DeAlloc(data);
		return true;
	}

	// .ShrinkToFit()
	CONSTEXPR20 bool ShrinkToFit()
	{
		if (IsFilled())
			return;

		char* data{ m_Buffer };

		try
		{
			AllocIterable(char, m_Buffer, m_Length);
		}
		catch (std::bad_alloc)
		{
			m_Buffer = data;
			return false;
		}

		CopyIterable(m_Buffer, 0, m_Length, data);
		DeAlloc(data);
		m_Buffer[m_Length] = '\0';
		m_Size = (m_Length + 1) * sizeof(char);

		return true;
	}

	// .StartsWith()
	CONSTEXPR20 const bool StartsWith(const char character) const
	{
		return *m_Buffer == character;
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

	// .SubStr()
	CONSTEXPR20 String SubStr(size_t startIndex, size_t endIndex) const
	{
		String data{ endIndex - startIndex };

		size_t i{};
		for (size_t j{ startIndex }; j < endIndex; ++j, ++i)
			data[i] = m_Buffer[j];

		return data;
	}

	CONSTEXPR20 String SubStrS(size_t startIndex, size_t endIndex) const
	{
		if (startIndex > m_Length)
			throw std::logic_error("Start Index is larger than m_Length!");

		if (endIndex > m_Length)
			throw std::logic_error("End Index is larger than m_Length!");

		if (startIndex > endIndex)
			throw std::logic_error("Start Index is larger than End Index!");

		String data{ endIndex - startIndex };

		size_t i{};
		for (size_t j{ startIndex }; j < endIndex; ++j, ++i)
			data[i] = m_Buffer[j];

		return data;
	}

	// .SubStrC()
	CONSTEXPR20 String SubStrC(size_t startIndex, size_t count) const
	{
		return SubStr(startIndex, startIndex + count);
	}

	CONSTEXPR20 String SubStrCS(size_t startIndex, size_t count) const
	{
		return SubStrS(startIndex, startIndex + count);
	}

	// .Swap()
	CONSTEXPR20 void Swap(String& other)
	{
		String temp{ std::move(other) };
		other = std::move(*this);
		*this = std::move(temp);
	}

	// .Title()
	CONSTEXPR20 String& Title()
	{
		if (m_Length == 0)
			return *this;

		int characterAsInt{ *m_Buffer };

		size_t i{};
		if (IsLowerChar(characterAsInt))
		{
			*m_Buffer -= 32;
			++i;
		}

		for (; i < m_Length; ++i)
		{
			characterAsInt = m_Buffer[i];

			// If Is White Space Character (space, \n, tab)
			if (characterAsInt == 32 || characterAsInt == 10 || characterAsInt == 9)
			{
				characterAsInt = m_Buffer[i + 1u];

				if (IsLowerChar(characterAsInt))
					m_Buffer[++i] -= 32;
			}
		}

		return *this;
	}

	// .ToLower()
	CONSTEXPR20 String& ToLower()
	{
		for (size_t i{}; i < m_Length; ++i)
		{
			int characterAsInt{ m_Buffer[i] };

			if (IsUpperChar(characterAsInt))
				m_Buffer[i] += 32;
		}

		return *this;
	}

	// .ToUpper()
	CONSTEXPR20 String& ToUpper()
	{
		for (size_t i{}; i < m_Length; ++i)
		{
			int characterAsInt{ m_Buffer[i] };

			if (IsLowerChar(characterAsInt))
				m_Buffer[i] -= 32;
		}

		return *this;
	}

	// .Upper()
	CONSTEXPR20 String Upper() const
	{
		return String{ *this }.ToUpper();
	}

	/*
	* 
	*	GETTERS AND SETTERS
	* 
	*/

	// .At()
	CONSTEXPR20 char& At(size_t index)
	{
		if (m_Length > index)
			return m_Buffer[index];

		throw std::out_of_range("Index out of bounds!");
	}

	CONSTEXPR20 const char At(size_t index) const
	{
		if (m_Length > index)
			return m_Buffer[index];

		throw std::out_of_range("Index out of bounds!");
	}

	// .begin()

	// non-const
	CONSTEXPR20 char* begin()
	{
		return m_Buffer;
	}

	// const
	CONSTEXPR20 const char* begin() const
	{
		return m_Buffer;
	}

	// .Data()

	// non-const
	CONSTEXPR20 char* Data()
	{
		return m_Buffer;
	}

	// const
	CONSTEXPR20 const char* Data() const
	{
		return m_Buffer;
	}

	// .end()

	// non-const
	CONSTEXPR20 char* end()
	{
		return m_Buffer + m_Length;
	}

	// const
	CONSTEXPR20 const char* end() const
	{
		return m_Buffer + m_Length;
	}

	// .Length()
	CONSTEXPR20 const size_t Length() const
	{
		return m_Length;
	}

	// .Size()
	CONSTEXPR20 const size_t Size() const
	{
		return m_Size;
	}

	/*
	* 
	*	OPERATORS
	* 
	*/

	// operator[]()
	CONSTEXPR20 char& operator[](size_t index)
	{
		return m_Buffer[index];
	}

	CONSTEXPR20 const char operator[](size_t index) const
	{
		return m_Buffer[index];
	}

	// operator=()
	CONSTEXPR20 String& operator=(const char* string)
	{
		m_Length = GetStrLen(string);
		m_Size = (m_Length + 1) * sizeof(char);

		DeAlloc(m_Buffer);
		AllocIterable(char, m_Buffer, m_Length);
		CopyIterable(m_Buffer, 0, m_Length, string);
		m_Buffer[m_Length] = '\0';

		return *this;
	}

	CONSTEXPR20 String& operator=(const std::string& string)
	{
		return *this = string.data(); // i.e. this->operator=(string.data());
	}

	CONSTEXPR20 String& operator=(const String& string)
	{
		return *this = string.m_Buffer; // i.e. this->operator=(string.m_Buffer);
	}

	CONSTEXPR20 String& operator=(String&& other) noexcept
	{
		m_Buffer = other.m_Buffer;
		m_Length = other.m_Length;
		m_Size = other.m_Size;

		other.ReAlloc();
		return *this;
	}

	// operator*=()
	CONSTEXPR20 void operator*=(const size_t count)
	{
		if (count == 0)
		{
			FillIterable(m_Buffer, 0, m_Length, '\0');
			m_Length = 0;
			return;
		}

		Reserve((m_Length * count + 1) * sizeof(char));

		{
			char* tempBuffer{ m_Buffer + m_Length };
			for (size_t i{ 1 }; i < count; ++i)
			{
				CopyIterable(tempBuffer, 0, m_Length, m_Buffer);
				tempBuffer += m_Length;
			}
		}

		m_Length *= count;
		m_Buffer[m_Length] = '\0';
	}

	// operator+()
	NODISCARD17 CONSTEXPR20 String operator+(const char character) const
	{
		String newStr{ m_Buffer, (m_Length + 2) * sizeof(char) };
		newStr[m_Length] = character;
		newStr[++newStr.m_Length] = '\0';

		return newStr;
	}

	NODISCARD17 CONSTEXPR20 String operator+(const char* string) const
	{
		size_t strCount{ GetStrLen(string) + 1 };
		String newStr{ m_Buffer, (m_Length + strCount) * sizeof(char) };

		char* tempNewStrBuffer{ newStr.m_Buffer + m_Length };
		CopyIterable(tempNewStrBuffer, 0, strCount, string);

		newStr.m_Length += strCount - 1;
		return newStr;
	}

	NODISCARD17 CONSTEXPR20 String operator+(const std::string& string) const
	{
		return (*this + string.data()); // i.e. this->operator+(string.data());
	}

	NODISCARD17 CONSTEXPR20 String operator+(const String& string) const
	{
		return (*this + string.m_Buffer); // i.e. this->operator+(string.m_Buffer);
	}

	// operator*()
	NODISCARD17 CONSTEXPR20 String operator*(size_t count) const
	{
		if (m_Length == 0)
			return {};

		size_t requiredLen{ count * m_Length };
		String newStr{ requiredLen };
		char* tempNewStrBuffer{ newStr.m_Buffer };

		while (count > 0)
		{
			CopyIterable(tempNewStrBuffer, 0, m_Length, m_Buffer);
			tempNewStrBuffer += m_Length;
			--count;
		}

		newStr.m_Length = requiredLen;
		return newStr;
	}

	// operator==()
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
		return *this == string.data(); // i.e. this->operator==(string.data());
	}

	CONSTEXPR20 bool operator==(const String& string) const
	{
		return *this == string.m_Buffer; // i.e. this->operator==(string.m_Buffer)
	}

	// operator!=()
	CONSTEXPR20 bool operator!=(const char* string) const
	{
		if (m_Length != GetStrLen(string)) return true;

		for (size_t i{}; i < m_Length; ++i)
			if (m_Buffer[i] != string[i])
				return true;

		return false;
	}

	CONSTEXPR20 bool operator!=(const std::string& string) const
	{
		return *this != string.data(); // i.e. this->operator!=(string.data())
	}

	CONSTEXPR20 bool operator!=(const String& string) const
	{
		return *this != string.m_Buffer; // i.e. this->operator!=(string.m_Buffer)
	}

	// operator>()
	CONSTEXPR20 bool operator>(const char* string) const
	{
		for (size_t i{}; i < m_Length; ++i)
			if (string[i] <= m_Buffer[i]) // i.e. m_Buffer[i] >= string[i]
				return true;

		return false;
	}

	CONSTEXPR20 bool operator>(const std::string& string) const
	{
		return *this > string.data(); // i.e. this->operator>(string.data())
	}

	CONSTEXPR20 bool operator>(const String& string) const
	{
		return *this > string.m_Buffer; // i.e. this->operator>(string.m_Buffer)
	}

	// operator<()
	CONSTEXPR20 bool operator<(const char* string) const
	{
		for (size_t i{}; i < m_Length; ++i)
			if (string[i] >= m_Buffer[i]) // i.e. m_Buffer[i] <= string[i]
				return true;

		return false;
	}

	CONSTEXPR20 bool operator<(const std::string& string) const
	{
		return *this < string.data(); // i.e. this->operator<(string.data())
	}

	CONSTEXPR20 bool operator<(const String& string) const
	{
		return *this < string.m_Buffer; // i.e. this->operator<(string.m_Buffer)
	}

	// operator>=()
	CONSTEXPR20 bool operator>=(const char* string) const
	{
		for (size_t i{}; i < m_Length; ++i)
			if (m_Buffer[i] >= string[i])
				return true;

		return false;
	}

	CONSTEXPR20 bool operator>=(const std::string& string) const
	{
		return *this >= string.data(); // i.e. this->operator>=(string.data())
	}

	CONSTEXPR20 bool operator>=(const String& string) const
	{
		return *this >= string.m_Buffer; // i.e. this->operator>=(string.m_Buffer)
	}

	// operator<=()
	CONSTEXPR20 bool operator<=(const char* string) const
	{
		for (size_t i{}; i < m_Length; ++i)
			if (m_Buffer[i] <= string[i])
				return false;

		return true;
	}

	CONSTEXPR20 bool operator<=(const std::string& string) const
	{
		return *this <= string.data(); // i.e. this->operator<=(string.data())
	}

	CONSTEXPR20 bool operator<=(const String& string) const
	{
		return *this <= string.m_Buffer; // i.e. this->operator<=(string.m_Buffer)
	}

	// operator std::string()
	operator std::string() const
	{
		return std::string{ m_Buffer };
	}

	// Destructor
	CONSTEXPR20 ~String()
	{
		DeAlloc(m_Buffer);
	}

private:
	template<typename T>
	CONSTEXPR20 void formatter(String& resultStr, const T& value, size_t& bracketCount, size_t& nextStartingPoint)
	{
		size_t openBracket{ Index('{', bracketCount) };

		if (openBracket != m_Length)
		{
			size_t closeBracket{ openBracket + 1 };
			size_t condition{ m_Buffer[closeBracket] != '}' };

			resultStr.Append(SubStr(nextStartingPoint, openBracket + condition).m_Buffer);

			++bracketCount;
			nextStartingPoint = closeBracket + (condition ^ 1);

			if (condition)
				formatter(resultStr, value, bracketCount, nextStartingPoint);
			else
				resultStr.Append(value);
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

// operator<<()
__forceinline std::ostream& operator<<(std::ostream& stream, const CTL::Dynamic::String& data)
{
	return stream << data.Data();
}

// GetStrLen()
template<typename T>
constexpr size_t GetStrLen(const T str)
{
	throw std::runtime_error("GetStrLen only accepts (char*, const char*, std::string, and CTL::Dynamic::String)!");
}

constexpr size_t GetStrLen(char* str)
{
	size_t i{};
	while (str[i] != '\0') ++i;

	return i;
}

constexpr size_t GetStrLen(const char* str)
{
	size_t i{};
	while (str[i] != '\0') ++i;

	return i;
}

CONSTEXPR20 size_t GetStrLen(const std::string& str)
{
	return str.length();
}

CONSTEXPR20 size_t GetStrLen(const CTL::Dynamic::String& str)
{
	return str.Length();
}

// operator""_DS()
NODISCARD17 CONSTEXPR20 CTL::Dynamic::String operator""_DS(const char* string, size_t strLength)
{
	return CTL::Dynamic::String{ string };
}