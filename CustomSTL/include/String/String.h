#pragma once

#include <ostream>

namespace CTL
{
	class String
	{
		friend std::ostream& operator<<(std::ostream& stream, const String& data);

	public:
		String();
		String(const String& other);

		explicit String(size_t count);
		explicit String(const char* string);
		explicit String(const std::string& string);

	public:
		char* begin();
		char* end();

	public:
		const char* begin() const;
		const char* end() const;
		const size_t Length() const;
		const size_t Size() const;

	public:
		bool Has(const char character) const;
		bool Has(const char* string) const;
		bool Has(const std::string& string) const;
		bool Has(const String& string) const;

	public:
		char& operator[](size_t index);

	public:
		const char& operator[](size_t index) const;

		String operator+(const char* string) const;
		String operator+(const std::string& string) const;
		String operator+(const String& other) const;

		bool operator==(const char* string) const;
		bool operator==(const std::string& string) const;
		bool operator==(const String& other) const;

		bool operator!=(const char* string) const;
		bool operator!=(const std::string& string) const;
		bool operator!=(const String& other) const;

		bool operator>(const char* string) const;
		bool operator>(const std::string& string) const;
		bool operator>(const String& other) const;

		bool operator<(const char* string) const;
		bool operator<(const std::string& string) const;
		bool operator<(const String& other) const;

		bool operator>=(const char* string) const;
		bool operator>=(const std::string& string) const;
		bool operator>=(const String& other) const;

		bool operator<=(const char* string) const;
		bool operator<=(const std::string& string) const;
		bool operator<=(const String& other) const;

	public:
		~String();

	private:
		size_t m_Length;
		size_t m_Size;
		char* m_Buffer;
	};

	std::ostream& operator<<(std::ostream& stream, const String& data);

};