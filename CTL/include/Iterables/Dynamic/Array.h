#pragma once

#include "CTL.h"
#include <vector>

// Foward Decl
_CTLBEGIN
_DYNAMICBEGIN
template<typename T>
class Array;
_DYNAMICEND
_CTLEND

template<typename Ts>
constexpr unsigned int GetItemsCount(const Ts& items)
{
	return 1u;
}

template<typename T, typename... Ts>
constexpr unsigned int GetItemsCount(const T& item, const Ts&... items)
{
	return 1u + GetItemsCount(items...);
}


template<typename T>
class CTL::Dynamic::Array
{
public:

	/*
	*
	*	CONSTRUCTORS
	*
	*/

	// IMPLICIT
	CONSTEXPR20 Array() : m_Length(0), m_Capacity(DEFAULT_CAPACITY)
	{
		AllocIterableInit(T, m_Buffer, DEFAULT_CAPACITY);
	}

	// EXPLICIT
	CONSTEXPR20 explicit Array(const size_t count) : m_Length(0), m_Capacity(count)
	{
		AllocIterableInit(T, m_Buffer, count);
	}

	CONSTEXPR20 explicit Array(const T* arr, const size_t length) : m_Length(length), m_Capacity(length)
	{
		AllocIterable(T, m_Buffer, m_Capacity);
		CopyIterable(m_Buffer, 0, m_Length, arr);
	}

	CONSTEXPR20 explicit Array(const T* arr, const size_t length, const size_t capacity) : m_Length(length), m_Capacity(capacity)
	{
		AllocIterable(T, m_Buffer, m_Capacity);
		CopyIterableInit(T, m_Buffer, 0, m_Length, m_Capacity, arr);
	}

	template<typename... Ts>
	CONSTEXPR20 explicit Array(const Ts&... items): m_Length(0), m_Capacity(GetItemsCount(items...))
	{
		if (!((std::is_same_v<T, Ts>)&&...))
			throw std::runtime_error("Hi");

		AllocIterable(T, m_Buffer, m_Capacity);
		((m_Buffer[m_Length] = items, ++m_Length), ...);
	}

	template<typename H, size_t length>
	CONSTEXPR20 explicit Array(const H(&arr)[length]) : m_Length(length), m_Capacity(length)
	{
		static_assert(std::is_same_v<T, H>, "Hi");

		AllocIterable(H, m_Buffer, length);
		CopyIterable(m_Buffer, 0, length, arr);
	}

	// COPY
	CONSTEXPR20 Array(const Array<T>& arr) : m_Length(arr.m_Length), m_Capacity(arr.m_Capacity)
	{
		AllocIterable(T, m_Buffer, m_Length + 1);
		CopyIterable(m_Buffer, 0, m_Length, arr.m_Buffer);
	}

	// MOVE
	CONSTEXPR20 Array(Array<T>&& arr) noexcept : m_Length(arr.m_Length), m_Capacity(arr.m_Capacity), m_Buffer(arr.m_Buffer)
	{
		arr.ReAlloc();
	}

	/*
	*
	*	.Methods()
	*
	*/

	// .Append()
	CONSTEXPR20 void Append(const T& item)
	{
		if (IsFilled())
		{
			m_Capacity *= 2;
			ReAllocIterable(T, m_Buffer, m_Length, m_Capacity);
		}

		m_Buffer[m_Length] = item;
		++m_Length;
	}

	CONSTEXPR20 void Append(const Array<T>& arr)
	{
		size_t newLen{ m_Length + arr.m_Length };

		if (m_Capacity < newLen)
		{
			m_Capacity = newLen * 2;
			ReAllocIterable(T, m_Buffer, m_Length, m_Capacity);
		}

		T* tempBuffer{ m_Buffer + m_Length };
		CopyIterable(tempBuffer, 0, arr.m_Length, arr);
		m_Length = newLen;
	}

	// .AppendAll()
	template<typename... Items>
	CONSTEXPR20 void AppendAll(const Items&... VarItems)
	{
		static_assert(
			((std::is_same_v<Items, T>)&&...),
			"Condition is not satisfied ! Got unexpected Data type...");

		size_t itemsLen{};

		Reserve((((VarItems, ++itemsLen), ...) + m_Length) * 2);
		((m_Buffer[m_Length] = VarItems, ++m_Length), ...);
	}

	// .Count()
	CONSTEXPR20 unsigned int Count(const T& item) const
	{
		unsigned int count{};

		for (size_t i{}; i < m_Length; ++i)
			if (m_Buffer[i] == item)
				++count;

		return count;
	}

	// .Find()

	// non-const
	CONSTEXPR20 T* Find(const T& item, unsigned int occurrenceNumber = 1u)
	{
		return m_Buffer + Index(item, occurrenceNumber);
	}

	// const
	CONSTEXPR20 const T* Find(const T item, unsigned int occurrenceNumber = 1u) const
	{
		return m_Buffer + Index(item, occurrenceNumber);
	}

	// .Has()
	CONSTEXPR20 bool Has(const T& item) const
	{
		return Index(item) != m_Length;
	}

	// .Index()
	CONSTEXPR20 size_t Index(const T& item, unsigned int occurrenceNumber = 1u) const
	{
		for (size_t i{}; i < m_Length; ++i)
			if (m_Buffer[i] == item && --occurrenceNumber == 0u)
				return i;

		return m_Length;
	}

	// .Insert()
	CONSTEXPR20 void Insert(const T& item, const size_t index)
	{
		if (index > m_Length)
		{
			throw std::logic_error("index is out of bounds!");
			return;
		}

		if (IsFilled())
		{
			m_Capacity *= 2;
			ReAllocIterable(T, m_Buffer, m_Length, m_Capacity);
		}

		ShiftToRight(m_Buffer, index, m_Length, 1);
		m_Buffer[index] = item;
		++m_Length;
	}

	CONSTEXPR20 void Insert(const Array<T>& arr, const size_t index)
	{
		if (arr.m_Length == 0)
			return;

		if (index > m_Length)
		{
			throw std::logic_error("index is out of bounds!");
			return;
		}

		if (IsFilled())
		{
			m_Capacity = (m_Capacity + arr.m_Length) * 2;
			ReAllocIterable(T, m_Buffer, m_Length, m_Capacity);
		}

		T* tempBuffer{ m_Buffer + index };

		ShiftToRight(m_Buffer, index, m_Length, arr.m_Length);
		CopyIterable(tempBuffer, 0, arr.m_Length, arr.m_Buffer);
		m_Length += arr.m_Length;
	}

	// .IsSomething()
	CONSTEXPR20 bool IsFilled() const
	{
		return m_Length == m_Capacity;
	}

	CONSTEXPR20 bool IsEmpty() const
	{
		return m_Length == 0;
	}

	// .Reserve()
	CONSTEXPR20 bool Reserve(const size_t count)
	{
		if (count <= m_Capacity)
			return false;

		T* oldBuffer{ m_Buffer };

		try
		{
			AllocIterable(T, m_Buffer, count);
		}
		catch (const std::bad_alloc&)
		{
			m_Buffer = oldBuffer;
			return false;
		}

		CopyIterableInit(T, m_Buffer, 0, m_Length, count, oldBuffer);
		m_Capacity = count;

		DeAlloc(oldBuffer);
		return true;
	}

	// .Reset()
	CONSTEXPR20 void ReAlloc() noexcept
	{
		m_Length = 0;
		m_Capacity = DEFAULT_CAPACITY;
		AllocIterableInit(T, m_Buffer, DEFAULT_CAPACITY);
	}

	CONSTEXPR20 void Reset() noexcept
	{
		DeAlloc(m_Buffer);
		m_Length = 0;
		m_Capacity = DEFAULT_CAPACITY;
		AllocIterableInit(T, m_Buffer, DEFAULT_CAPACITY);
	}

	// .Replace()
	CONSTEXPR20 Array<T>& Replace(const T& toFindItem, const T& toReplItem)
	{
		for (size_t i{}; i < m_Length; ++i)
			if (m_Buffer[i] == toFindItem)
				m_Buffer[i] = toReplItem;
	}

	CONSTEXPR20 Array<T>& Replace(const T& toFindItem, const T& toReplItem, unsigned int numberOfReplaces)
	{
		if (numberOfReplaces == 0)
			return;

		for (size_t i{}; i < m_Length; ++i)
			if (m_Buffer[i] == toFindItem)
			{
				m_Buffer[i] = toReplItem;
				if (--numberOfReplaces == 0)
					return;
			}
	}

	// .ReverseIndex()
	CONSTEXPR20 size_t ReverseIndex(const T& item, unsigned int occurrenceNumber = 1u) const
	{
		size_t i{ m_Length };
		while (i > 0)
		{
			--i;
			if (m_Buffer[i] == item && --occurrenceNumber == 0u)
				return i;
		}

		return m_Length;
	}

	// .Shrink()
	CONSTEXPR20 bool Shrink(size_t count)
	{
		if (count == m_Capacity)
			return true;

		if (count > m_Capacity || count < m_Length)
			return false;

		T* data{ m_Buffer };

		try
		{
			AllocIterable(T, m_Buffer, count);
		}
		catch (const std::bad_alloc&)
		{
			m_Buffer = data;
			return false;
		}

		m_Capacity = count;
		CopyIterableInit(char, m_Buffer, 0, m_Length, m_Capacity, data);

		DeAlloc(data);
		return true;
	}

	// .ShrinkToFit()
	CONSTEXPR20 bool ShrinkToFit()
	{
		return Shrink(m_Length);
	}

	// .SubStr()
	CONSTEXPR20 Array<T> Slice(size_t startIndex, size_t endIndex = 0, size_t steps = 1) const
	{
		endIndex = (endIndex > 0) ? endIndex : m_Length;
		Array<T> data{ endIndex - startIndex };

		size_t i{};
		for (size_t j{ startIndex }; j < endIndex; j += steps, ++i)
			data[i] = m_Buffer[j];

		return data;
	}

	CONSTEXPR20 Array<T> SliceS(size_t startIndex, size_t endIndex = 0, size_t steps = 1) const
	{
		endIndex = (endIndex > 0) ? endIndex : m_Length;

		if (startIndex > m_Length)
			throw std::logic_error("Start Index is larger than m_Length!");

		if (endIndex > m_Length)
			throw std::logic_error("End Index is larger than m_Length!");

		if (steps == 0)
			throw std::logic_error("Steps is 0! Why?!");

		if (startIndex > endIndex)
			throw std::logic_error("Start Index is larger than End Index!");

		Array<T> data{ endIndex - startIndex };

		size_t i{};
		for (size_t j{ startIndex }; j < endIndex; j += steps, ++i)
			data[i] = m_Buffer[j];

		return data;
	}

	// .SubStrC()
	CONSTEXPR20 Array<T> SliceC(size_t startIndex, size_t count, size_t steps = 0) const
	{
		return Slice(startIndex, startIndex + count, steps);
	}

	CONSTEXPR20 Array<T> SliceCS(size_t startIndex, size_t count, size_t steps = 0) const
	{
		return SliceS(startIndex, startIndex + count, steps);
	}

	// .Swap()
	CONSTEXPR20 void Swap(Array<T>& other)
	{
		T* tempBuffer{ other.m_Buffer };
		size_t tempLen{ other.m_Length };
		size_t tempCap{ other.m_Capacity };

		other.m_Buffer = m_Buffer;
		other.m_Length = m_Length;
		other.m_Capacity = m_Capacity;

		m_Buffer = tempBuffer;
		m_Length = m_Length;
		m_Capacity = m_Capacity;
	}

	/*
	*
	*	GETTERS AND SETTERS
	*
	*/

	// .At()
	CONSTEXPR20 T& At(size_t index)
	{
		if (m_Length > index)
			return m_Buffer[index];

		throw std::out_of_range("Index out of bounds!");
	}

	CONSTEXPR20 const T& At(size_t index) const
	{
		if (m_Length > index)
			return m_Buffer[index];

		throw std::out_of_range("Index out of bounds!");
	}

	// .begin()

	// non-const
	CONSTEXPR20 T* begin()
	{
		return m_Buffer;
	}

	// const
	CONSTEXPR20 const T* begin() const
	{
		return m_Buffer;
	}

	// .Data()

	// non-const
	CONSTEXPR20 T* Data()
	{
		return m_Buffer;
	}

	// const
	CONSTEXPR20 const T* Data() const
	{
		return m_Buffer;
	}

	// .end()

	// non-const
	CONSTEXPR20 T* end()
	{
		return m_Buffer + m_Length;
	}

	// const
	CONSTEXPR20 const T* end() const
	{
		return m_Buffer + m_Length;
	}

	// .Length()
	CONSTEXPR20 const size_t Length() const
	{
		return m_Length;
	}

	// .Size()
	CONSTEXPR20 const size_t Capacity() const
	{
		return m_Capacity;
	}

	/*
	*
	*	OPERATORS
	*
	*/

	// operator[]()
	CONSTEXPR20 T& operator[](size_t index)
	{
		return m_Buffer[index];
	}

	CONSTEXPR20 const T& operator[](size_t index) const
	{
		return m_Buffer[index];
	}

	// operator=()
	CONSTEXPR20 Array<T>& operator=(const Array<T>& arr)
	{
		if (m_Length >= arr.m_Length)
		{
			m_Length = arr.m_Length;
			CopyIterableInit(T, m_Buffer, 0, m_Length, m_Capacity, arr);
			
			return *this;
		}

		m_Length = arr.m_Length;
		m_Capacity = arr.m_Capacity;

		DeAlloc(m_Buffer);
		AllocIterable(T, m_Buffer, m_Capacity);
		CopyIterable(m_Buffer, 0, m_Length, arr);

		return *this;
	}

	CONSTEXPR20 Array<T>& operator=(Array<T>&& other) noexcept
	{
		DeAlloc(m_Buffer);

		m_Buffer = other.m_Buffer;
		m_Length = other.m_Length;
		m_Capacity = other.m_Capacity;

		other.ReAlloc();
		return *this;
	}

	// operator*=()
	CONSTEXPR20 void operator*=(const size_t multiplier)
	{
		if (multiplier == 0)
		{
			FillIterable(m_Buffer, 0, m_Length, T{});
			m_Length = 0;
			return;
		}

		Reserve(m_Length * multiplier);

		T* tempBuffer{ m_Buffer + m_Length };
		for (size_t i{ 1 }; i < multiplier; ++i)
		{
			CopyIterable(tempBuffer, 0, m_Length, m_Buffer);
			tempBuffer += m_Length;
		}

		m_Length *= multiplier;
	}

	// operator+()
	NODISCARD17 CONSTEXPR20 Array<T> operator+(const T& item) const
	{
		Array<T> newArr{ m_Buffer, m_Length + 1 };
		newArr.m_Buffer[m_Length] = item;

		return newArr;
	}

	NODISCARD17 CONSTEXPR20 Array<T> operator+(const Array<T>& arr) const
	{
		size_t arrLen{ arr.m_Length };
		Array<T> newArr{ m_Buffer, m_Length + arrLen };

		T* tempNewArrBuffer{ newArr.m_Buffer + m_Length };
		CopyIterable(tempNewArrBuffer, 0, arrLen, arr);

		return newStr;
	}

	// operator*()
	NODISCARD17 CONSTEXPR20 Array<T> operator*(size_t multiplier) const
	{
		if (m_Length == 0)
			return {};

		size_t requiredLen{ multiplier * m_Length };
		Array<T> newArr{ requiredLen };
		T* tempNewArrBuffer{ newArr.m_Buffer };

		while (multiplier > 0)
		{
			CopyIterable(tempNewArrBuffer, 0, m_Length, m_Buffer);
			tempNewArrBuffer += m_Length;
			--multiplier;
		}

		newArr.m_Length = requiredLen;
		return newArr;
	}

	// operator==()
	CONSTEXPR20 bool operator==(const Array<T>& arr) const
	{
		if (m_Length != arr.m_Length) return false;

		for (size_t i{}; i < m_Length; ++i)
			if (m_Buffer[i] != arr[i])
				return false;

		return true;
	}

	// operator!=()
	CONSTEXPR20 bool operator!=(const Array<T>& arr) const
	{
		if (m_Length != arr.m_Length) return true;

		for (size_t i{}; i < m_Length; ++i)
			if (m_Buffer[i] != arr[i])
				return true;

		return false;
	}

	// operator>()
	CONSTEXPR20 bool operator>(const Array<T>& arr) const
	{
		for (size_t i{}; i < m_Length; ++i)
			if (m_Buffer[i] > arr[i])
				return true;

		return false;
	}

	// operator<()
	CONSTEXPR20 bool operator<(const Array<T>& arr) const
	{
		for (size_t i{}; i < m_Length; ++i)
			if (m_Buffer[i] < arr[i])
				return true;

		return false;
	}

	// operator>=()
	CONSTEXPR20 bool operator>=(const Array<T>& arr) const
	{
		for (size_t i{}; i < m_Length; ++i)
			if (m_Buffer[i] >= arr[i])
				return true;

		return false;
	}

	// operator<=()
	CONSTEXPR20 bool operator<=(const Array<T>& arr) const
	{
		for (size_t i{}; i < m_Length; ++i)
			if (m_Buffer[i] <= arr[i])
				return false;

		return true;
	}

	// operator std::string()
	operator std::vector<T>() const
	{
		std::vector<T> tempVec{};

		tempVec.reserve(m_Capacity);

		for (size_t i{}; i < m_Length; ++i)
			tempVec.push_back(m_Buffer[i]);

		return tempVec;
	}

	// Destructor
	CONSTEXPR20 ~Array()
	{
		DeAlloc(m_Buffer);
	}

public:
	constexpr static void SetDefaultCapacity(const size_t value)
	{
		if (value > 0)
			DEFAULT_CAPACITY = value;
	}

private:
	size_t m_Length;
	size_t m_Capacity;
	T* m_Buffer;

	inline static size_t DEFAULT_CAPACITY{ 15 };
};

// operator<<()
template<typename T>
__forceinline std::ostream& operator<<(std::ostream& stream, const CTL::Dynamic::Array<T>& data)
{
	for (size_t i{}; i < data.Length(); ++i)
		stream << data[i] << ' ';

	return stream;
}