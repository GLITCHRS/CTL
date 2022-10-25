#include "Tests.h"

void PrintStr(const CTL::Dynamic::String& str, const char* funcName, int line)
{
	std::cout << "==============================\n";
	std::cout << "Called by: " << funcName << ", " << line << '\n';
	std::cout << str << '\n';
	std::cout << str.Length() << '\n';
	std::cout << str.Size() << '\n';
	std::cout << "==============================\n";
}

void Test1()
{
	CTL::Dynamic::String a{};
	CTL::Dynamic::String b{ 100 };
	CTL::Dynamic::String c{ "My name is, Ahmed." };
	CTL::Dynamic::String d{ c };
	CTL::Dynamic::String e{ d };
	CTL::Dynamic::String f{ std::move(d) };

	LOGStr(a);
	LOGStr(b);
	LOGStr(c);
	LOGStr(d);
	LOGStr(e);
	LOGStr(f);
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

void Test3()
{
	CTL::Dynamic::String a{};

	a.Append('M');
	a.Append('y');
	a.Append(" Name");
	a.Append(" Is");
	a.Append(" Ahmed");
	a.Append(" Zaki! LOL.");

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

//void Test4()
//{
//	CTL::Dynamic::String a{ "abcdc" };
//
//	std::cout << a.Has('a') << '\n';
//	std::cout << a.Has("a") << '\n';
//	std::cout << a.Has("ab") << '\n';
//	std::cout << a.Has('c') << '\n';
//	std::cout << a.Has("dc") << '\n';
//	std::cout << a.Has("cdc") << '\n';
//	std::cout << a.Has("cdc") << '\n';
//	std::cout << a.Has("bcd") << '\n';
//	std::cout << a.Has("bd") << '\n';
//}
//
//void Test5()
//{
//	const CTL::Dynamic::String a{ "abcdc" };
//
//	const char* data1{ a.Find('a')};
//	const char* data2{ a.Find("a")};
//	const char* data3{ a.Find("ab")};
//	const char* data4{ a.Find('c')};
//	const char* data5{ a.Find("dc")};
//	const char* data6{ a.Find("cdc")};
//	const char* data7{ a.Find("cdc")};
//	const char* data8{ a.Find("bcd")};
//	const char* data9{ a.Find("bd") };
//
//	if (data1)
//		std::cout << data1 << '\n';
//
//	if (data2)
//		std::cout << data2 << '\n';
//
//	if (data3)
//		std::cout << data3 << '\n';
//
//	if (data4)
//		std::cout << data4 << '\n';
//
//	if (data5)
//		std::cout << data5 << '\n';
//
//	if (data6)
//		std::cout << data6 << '\n';
//
//	if (data7)
//		std::cout << data7 << '\n';
//
//	if (data8)
//		std::cout << data8 << '\n';
//
//	if (data9)
//		std::cout << data9 << '\n';
//}
//
//void Test6()
//{
//	const CTL::Dynamic::String a{ "abcdc" };
//
//	std::cout << a.Index('a') << '\n';
//	std::cout << a.Index("a") << '\n';
//	std::cout << a.Index("ab") << '\n';
//	std::cout << a.Index('c') << '\n';
//	std::cout << a.Index("dc") << '\n';
//	std::cout << a.Index("cdc") << '\n';
//	std::cout << a.Index("cdc") << '\n';
//	std::cout << a.Index("bcd") << '\n';
//	std::cout << a.Index("bd") << '\n';
//}
//
//void Test7()
//{
//	const CTL::Dynamic::String a{ "abcdc" };
//
//	std::cout << a.Count('a') << '\n';
//	std::cout << a.Count("a") << '\n';
//	std::cout << a.Count("ab") << '\n';
//	std::cout << a.Count('c') << '\n';
//	std::cout << a.Count("dc") << '\n';
//	std::cout << a.Count("cdc") << '\n';
//	std::cout << a.Count("cdc") << '\n';
//	std::cout << a.Count("bcd") << '\n';
//	std::cout << a.Count("bd") << '\n';
//}
//
//void Test8()
//{
//	const CTL::Dynamic::String a{ "abcdc" };
//
//	for (char item : a)
//		std::cout << item;
//
//	std::cout << '\n';
//
//	std::cout << a.begin() << '\n';
//	std::cout << static_cast<int>(a.end()[0]) << '\n';
//}
//
//void Test9()
//{
//	CTL::Dynamic::String a{ "abcdc" };
//	const CTL::Dynamic::String b{ "abcdc" };
//
//	std::cout << a.Data() << '\n';
//	std::cout << b.Data() << '\n';
//	std::cout << "Hello"_DS.Data() << '\n';
//}
//
//void Test10()
//{
//	CTL::Dynamic::String a{ "abcdc" };
//	const CTL::Dynamic::String b{ "abcdc" };
//
//	std::cout << a.Length() << '\n';
//	std::cout << a.Size() << '\n';
//	std::cout << b.Length() << '\n';
//	std::cout << b.Size() << '\n';
//	std::cout << "Hello"_DS.Length() << '\n';
//	std::cout << "Hello"_DS.Size() << '\n';
//}
//
//void Test11()
//{
//	CTL::Dynamic::String a{ "abcdc" };
//	const CTL::Dynamic::String b{ "Hello" };
//
//	std::cout << a.SubStr(a.Length() / 2, a.Length()) << '\n';
//	std::cout << b.SubStr(b.Length() / 2, b.Length()) << '\n';
//}
//
//void Test12()
//{
//	CTL::Dynamic::String a{ "abcdc" };
//
//	std::cout << a.StartsWith('a') << '\n';
//	std::cout << a.StartsWith("a") << '\n';
//	std::cout << a.StartsWith("ab") << '\n';
//	std::cout << a.StartsWith('c') << '\n';
//	std::cout << a.StartsWith("dc") << '\n';
//	std::cout << a.StartsWith("cdc") << '\n';
//	std::cout << a.StartsWith("cdc") << '\n';
//	std::cout << a.StartsWith("bcd") << '\n';
//	std::cout << a.StartsWith("bd") << '\n';
//}
//
//void Test13()
//{
//	CTL::Dynamic::String a{ "abcdc" };
//
//	std::cout << a.EndsWith('a') << '\n';
//	std::cout << a.EndsWith("a") << '\n';
//	std::cout << a.EndsWith("ab") << '\n';
//	std::cout << a.EndsWith('c') << '\n';
//	std::cout << a.EndsWith("dc") << '\n';
//	std::cout << a.EndsWith("cdc") << '\n';
//	std::cout << a.EndsWith("cdc") << '\n';
//	std::cout << a.EndsWith("bcd") << '\n';
//	std::cout << a.EndsWith("bd") << '\n';
//}