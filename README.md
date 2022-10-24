# Dynamic String Class ~Done
- ## Constructors Done
	- ### Implicit Done
		- ```
			String(); Done
	- ### Explicit Done
		- ```
			String(const char*, requiredSize = 0); Done
			String(const std::string&); Done
			String(const size_t count); Done
	- ### Copy Done
		- ```
			String(const String&); Done
	- ### Move Done
		- ```
			String(String&&); Done
- ## Getters and setters Done
	- ### Getters Done
		-	#### Const Done
			-	```
				- Data(); Done
				- Length(); Done
				- Size(); Done
				- begin(); Done
				- end(); Done
		-	#### Non-Const Done
			-	```
				- Data(); Done
				- begin(); Done
				- end(); Done
- ## Overloaded Operators Done
	- ### Non-Const Done
		- ```
			- operator=(const char*); Done
			- operator=(const std::string&); Done
			- operator=(const String&); Done
		- ```
			- operator+=(const char); Done
			- operator+=(const char*); Done
			- operator+=(const std::string&); Done
			- operator+=(const String&); Done
		- ```
			- operator*=(const size_t); Done
	- ### Const Done
		- ```
			- operator+(const char); Done
			- operator+(const char*); Done
			- operator+(const std::string&); Done
			- operator+(const String&); Done
		- ```
			- operator*(const size_t); Done
		- ```
			- operator==(const char*); Done
			- operator==(const std::string&); Done
			- operator==(const String&); Done
		- ```
			- operator!=(const char*); Done
			- operator!=(const std::string&); Done
			- operator!=(const String&); Done
		- ```
			- operator>(const char*); Done
			- operator>(const std::string&); Done
			- operator>(const String&); Done
		- ```
			- operator<(const char*); Done
			- operator<(const std::string&); Done
			- operator<(const String&); Done
		- ```
			- operator>=(const char*); Done
			- operator>=(const std::string&); Done
			- operator>=(const String&); Done
		- ```
			- operator<=(const char*); Done
			- operator<=(const std::string&); Done
			- operator<=(const String&); Done
- ## Methods ~Done
	- ### Const ~Done
		- ```
			- SubStr(size_t, size_t); !Done
		- ```
			- Has(const char character); Done
			- Has(const char* character); Done
			- Has(const std::string& character); Done
			- Has(const String& character); Done
		- ```
			- Count(const char); Done
			- Count(const char*); Done
			- Count(const std::string&); Done
			- Count(const String&); Done
		- ```
			- StartsWith(const char); Done
			- StartsWith(const char*); Done
			- StartsWith(const std::string&); Done
			- StartsWith(const String&); Done
		- ```
			- EndsWith(const char); Done
			- EndsWith(const char*); Done
			- EndsWith(const std::string&); Done
			- EndsWith(const String&); Done
		- ```
			- Find(const char); Done
			- Find(const char*); Done
			- Find(const std::string&); Done
			- Find(const String&); Done
		- ```
			- Index(const char); Done
			- Index(const char*); Done
			- Index(const std::string&); Done
			- Index(const String&); Done
		- ```
			- Split(const char); !Done # Later-Phase
			- Format(T...); !Done
		- ```
			- IsAlnum(); !Done
			- IsAlpha(); !Done
			- IsDigit(); !Done
			- IsLower(); !Done
			- IsUpper(); !Done
			- IsTItle(); !Done

	- ### Non-Const ~Done
		- ```
			- SubStr(size_t, size_t); !Done
		- ```
			- reserve(const size_t); Done
		- ```
			- append(const char); !Done
			- append(const char*); Done
			- append(const std::string&); Done
			- append(const String&); Done
		- ```
			- Lower(); !Done
			- Upper(); !Done
		- ```
			- Capitalize(); !Done
			- Title(); !Done
		- ```
			- Find(const char); Done
			- Find(const char*); Done
			- Find(const std::string&); Done
			- Find(const String&); Done
		- ```
			- Swap(String&); !Done
		- ```
			- Replace(const char, const char); !Done
			- Replace(const char*, const char*); !Done
			- Replace(const std::string&, const std::string&); !Done
			- Replace(const String&, const String&); !Done

# Separate Overloaded Operators Done
- `Operator ""_DS(string, length);` Done
