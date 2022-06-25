#pragma once

#include <ostream>

namespace CustomSTL
{
	class String
	{
		friend std::ostream& operator<<(std::ostream& stream, const String& data);

	public:
		String();
		String(size_t count);
		String(const char* string);
		String(const String& other);
		String(const std::string& string);

	public:
		const size_t Count() const;
		const size_t Size() const;

	public:
		String operator+(const char* string) const;
		String operator+(const String& other) const;
		String operator+(const std::string& string) const;

	public:
		~String();

	private:
		size_t m_Count;
		size_t m_Size;
		char* m_Buffer;
	};

	std::ostream& operator<<(std::ostream& stream, const String& data);

};