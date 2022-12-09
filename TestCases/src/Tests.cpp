#include "Tests.h"

void PrintStr(const CTL::Dynamic::String& str, const char* funcName, int line)
{
	std::cout << "==============================\n";
	std::cout << "Called by: " << funcName << ", " << line << '\n';
	std::cout << str << '\n';
	std::cout << str.Length() << '\n';
	std::cout << str.Capacity() << '\n';
	std::cout << "==============================\n";
}

void ConstructorsTest()
{
	CTL::Dynamic::String a{};
	CTL::Dynamic::String b{ 100 };
	CTL::Dynamic::String c{ "My name is, Ahmed." };
	CTL::Dynamic::String d{ "My name is, Ahmed.", 100 };
	CTL::Dynamic::String e{ std::string{"Hi"} };
	CTL::Dynamic::String f{ e };
	CTL::Dynamic::String g{ std::move(f) };

	LOGStr(a);
	LOGStr(b);
	LOGStr(c);
	LOGStr(d);
	LOGStr(e);
	LOGStr(f);
	LOGStr(g);
}

void AppendTest()
{
	using namespace std::string_literals;

	CTL::Dynamic::String a{};
	CTL::Dynamic::String b{};

	a.Append('M');
	a.Append('y');
	a.Append(" Name");
	a.Append(" Is"s);
	a.Append(" Ahmed."_DS);

	b.AppendAll("My", " Name", " Is"s, " Ahmed."_DS);

	LOGStr(a);
	LOGStr(b);
}

void CapitalizeTest()
{
	CTL::Dynamic::String a{ "My name is, Ahmed." };
	CTL::Dynamic::String b{ "my name is, Ahmed." };

	a.Capitalize();
	b.Capitalize();

	LOGStr(a);
	LOGStr(b);
}

void CountTest()
{
	const CTL::Dynamic::String a{ "abcdc" };

	std::cout << a.Count('a') << '\n';
	std::cout << a.Count("a") << '\n';
	std::cout << a.Count("ab") << '\n';
	std::cout << a.Count('c') << '\n';
	std::cout << a.Count("dc") << '\n';
	std::cout << a.Count("cdc") << '\n';
	std::cout << a.Count("bcd") << '\n';
	std::cout << a.Count("bd") << '\n';
}

void EndsWithTest()
{
	CTL::Dynamic::String a{ "abcdc" };

	std::cout << a.EndsWith('a') << '\n';
	std::cout << a.EndsWith("a") << '\n';
	std::cout << a.EndsWith("ab") << '\n';
	std::cout << a.EndsWith('c') << '\n';
	std::cout << a.EndsWith("c") << '\n';
	std::cout << a.EndsWith("dc") << '\n';
	std::cout << a.EndsWith("cdc") << '\n';
	std::cout << a.EndsWith("bcd") << '\n';
	std::cout << a.EndsWith("bd") << '\n';
}

void FindTest()
{
	const CTL::Dynamic::String a{ "abcdc" };

	const char* data1{ a.Find('a') };
	const char* data2{ a.Find("a") };
	const char* data3{ a.Find("ab") };
	const char* data4{ a.Find('c') };
	const char* data5{ a.Find("c")};
	const char* data6{ a.Find("dc") };
	const char* data7{ a.Find("cdc") };
	const char* data8{ a.Find("bcd") };
	const char* data9{ a.Find("bd") };

	if (data1)
		std::cout << data1 << '\n';

	if (data2)
		std::cout << data2 << '\n';

	if (data3)
		std::cout << data3 << '\n';

	if (data4)
		std::cout << data4 << '\n';
	
	if (data5)
		std::cout << data5 << '\n';

	if (data6)
		std::cout << data6 << '\n';

	if (data7)
		std::cout << data7 << '\n';

	if (data8)
		std::cout << data8 << '\n';

	if (data9)
		std::cout << data9 << '\n';
}

void FormatTest()
{
	CTL::Dynamic::String a{ "Hi {} Hello {}" };

	std::cout << a << '\n';
	std::cout << a.Format("Ahmed") << '\n';
	std::cout << a.Format("Ahmed", "Asem") << '\n';
	std::cout << a.Format("Ahmed", "Asem", "Khalid") << '\n';
}

void HasTest()
{
	CTL::Dynamic::String a{ "abcdc" };

	std::cout << a.Has('a') << '\n';
	std::cout << a.Has("a") << '\n';
	std::cout << a.Has("ab") << '\n';
	std::cout << a.Has('c') << '\n';
	std::cout << a.Has("c") << '\n';
	std::cout << a.Has("dc") << '\n';
	std::cout << a.Has("cdc") << '\n';
	std::cout << a.Has("bcd") << '\n';
	std::cout << a.Has("bd") << '\n';
}

void IndexTest()
{
	const CTL::Dynamic::String a{ "abcdc" };

	std::cout << a.Index('a') << '\n';
	std::cout << a.Index("a") << '\n';
	std::cout << a.Index("ab") << '\n';
	std::cout << a.Index('c') << '\n';
	std::cout << a.Index("c") << '\n';
	std::cout << a.Index("dc") << '\n';
	std::cout << a.Index("cdc") << '\n';
	std::cout << a.Index("bcd") << '\n';
	std::cout << a.Index("bd") << '\n';
}

void InsertTest()
{
	CTL::Dynamic::String a{ "is ahmed"};

	a.Insert('M', 0);
	std::cout << a << '\n';
	a.Insert('y', 1);
	std::cout << a << '\n';
	a.Insert(" Name ", 2);
	std::cout << a << '\n';
}

void Test2()
{
	CTL::Dynamic::String a{};

	LOGStr(a);
	a.Reserve(3);
	LOGStr(a);
	a = "Ab";
	LOGStr(a);
	a.Reserve(17);
	LOGStr(a);
	a.Reserve(0);
	LOGStr(a);
}

void Test4()
{
	CTL::Dynamic::String a{};

	using namespace std::string_literals;

	LOGStr(a);
	a.AppendAll("Hi", "Hi2"s, "Hi3"_DS);
	LOGStr(a);
	a.AppendAll(", "s, "Is", " Me"_DS);
	LOGStr(a);
	a.AppendAll("\nNEW"_DS, " STRING"_DS);
	LOGStr(a);
}

void Test9()
{
	const CTL::Dynamic::String a{ "abcdc" };

	for (char item : a)
		std::cout << item;

	std::cout << '\n';

	std::cout << a.begin() << '\n';
	std::cout << static_cast<int>(a.end()[0]) << '\n';
}

void Test10()
{
	CTL::Dynamic::String a{ "abcdc" };
	const CTL::Dynamic::String b{ "abcdc" };

	std::cout << a.Data() << '\n';
	std::cout << b.Data() << '\n';
	std::cout << "Hello"_DS.Data() << '\n';
}

void Test11()
{
	CTL::Dynamic::String a{ "abcdc" };
	const CTL::Dynamic::String b{ "abcdc" };

	std::cout << a.Length() << '\n';
	std::cout << a.Capacity() << '\n';
	std::cout << b.Length() << '\n';
	std::cout << b.Capacity() << '\n';
	std::cout << "Hello"_DS.Length() << '\n';
	std::cout << "Hello"_DS.Capacity() << '\n';
}

void Test12()
{
	CTL::Dynamic::String a{ "abcdc" };
	const CTL::Dynamic::String b{ "Hello" };

	std::cout << a.SubStr(a.Length() / 2, a.Length()) << '\n';
	std::cout << b.SubStr(b.Length() / 2, b.Length()) << '\n';
}

void Test13()
{
	CTL::Dynamic::String a{ "abcdc" };

	std::cout << a.StartsWith('a') << '\n';
	std::cout << a.StartsWith("a") << '\n';
	std::cout << a.StartsWith("ab") << '\n';
	std::cout << a.StartsWith('c') << '\n';
	std::cout << a.StartsWith("dc") << '\n';
	std::cout << a.StartsWith("cdc") << '\n';
	std::cout << a.StartsWith("cdc") << '\n';
	std::cout << a.StartsWith("bcd") << '\n';
	std::cout << a.StartsWith("bd") << '\n';
}