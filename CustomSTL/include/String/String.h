#pragma once

#include <ostream>

namespace CustomSTL
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
		const size_t Count() const;
		const size_t Size() const;

	public:
		bool Has(const char character) const;
		bool Has(const char* string) const;
		bool Has(const std::string& string) const;
		bool Has(const String& string) const;

	public:
		String operator+(const char* string) const;
		String operator+(const std::string& string) const;
		String operator+(const String& other) const;

		bool operator==(const char* string) const;
		bool operator==(const std::string& string) const;
		bool operator==(const String& other) const;

		bool operator!=(const char* string) const;
		bool operator!=(const std::string& string) const;
		bool operator!=(const String& other) const;

		bool operator>=(const char* string) const;
		bool operator>=(const std::string& string) const;
		bool operator>=(const String& other) const;

		bool operator<=(const char* string) const;
		bool operator<=(const std::string& string) const;
		bool operator<=(const String& other) const;

		bool operator>(const char* string) const;
		bool operator>(const std::string& string) const;
		bool operator>(const String& other) const;

		bool operator<(const char* string) const;
		bool operator<(const std::string& string) const;
		bool operator<(const String& other) const;

	public:
		~String();

	private:
		size_t m_Count;
		size_t m_Size;
		char* m_Buffer;
	};

	std::ostream& operator<<(std::ostream& stream, const String& data);

};