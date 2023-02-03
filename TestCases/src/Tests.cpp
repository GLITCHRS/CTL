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

void IsSomethingTest()
{
	CTL::Dynamic::String a{ "ahmed 5" };
	CTL::Dynamic::String b{ "Ahmed 5" };
	CTL::Dynamic::String c{ "55 A" };

	std::cout << a.IsAlnum() << '\n';
	std::cout << a.IsAlpha() << '\n';
	std::cout << a.IsDigit() << '\n';
	std::cout << a.IsLower() << '\n';
	std::cout << a.Upper().IsUpper() << '\n';
	std::cout << a.IsTitle() << '\n';

	std::cout << "------------------\n";

	std::cout << b.IsAlnum() << '\n';
	std::cout << b.IsAlpha() << '\n';
	std::cout << b.IsDigit() << '\n';
	std::cout << b.Lower().IsLower() << '\n';
	std::cout << b.IsUpper() << '\n';
	std::cout << b.IsTitle() << '\n';

	std::cout << "------------------\n";

	std::cout << c.IsAlnum() << '\n';
	std::cout << c.IsAlpha() << '\n';
	std::cout << c.IsDigit() << '\n';
	std::cout << c.IsLower() << '\n';
	std::cout << c.Upper().IsUpper() << '\n';
	std::cout << c.IsTitle() << '\n';
}

void LowerTest()
{
	CTL::Dynamic::String a{"AHMED"};
	std::cout << a.Lower() << '\n';
}

void Reserve()
{
	CTL::Dynamic::String a{};

	LOGStr(a);
	a.Reserve(3);
	LOGStr(a);
	a = "Ab";
	LOGStr(a);
	a.Reserve(17);
	LOGStr(a);
	a.Reserve(1);
	LOGStr(a);
	a.Reserve(0);
	LOGStr(a);
}

void Reset()
{
	CTL::Dynamic::String a{ "Ahmed" };

	LOGStr(a);
	a.Reset();
	LOGStr(a);
}

void Replace()
{
	CTL::Dynamic::String a{ "Ahmed" };

	LOGStr(a);
	LOGStr(a.Replace('A', 'm'));
	LOGStr(a.Replace("A", "M"));
	LOGStr(a.Replace('A', "KHALID"));
	LOGStr(a.Replace("med", "CHILD"));
	LOGStr(a.Replace("hm", 'b'));
}

void RIndex()
{
	CTL::Dynamic::String a{ "aeeea" };

	std::cout << a.RIndex('e') << '\n';
	std::cout << a.RIndex('a') << '\n';
	std::cout << a.RIndex('a', 2) << '\n';
}

void Shrinking()
{
	CTL::Dynamic::String a{ "aeeea", 100 };

	LOGStr(a);
	a.Shrink(55);
	LOGStr(a);
	a.ShrinkToFit();
	LOGStr(a);
	a.Shrink(101);
	LOGStr(a);
}

void StartsWith()
{
	CTL::Dynamic::String a{ "abcdc" };

	std::cout << a.StartsWith('a') << '\n';
	std::cout << a.StartsWith("a") << '\n';
	std::cout << a.StartsWith("ab") << '\n';
	std::cout << a.StartsWith('c') << '\n';
	std::cout << a.StartsWith("dc") << '\n';
	std::cout << a.StartsWith("cdc") << '\n';
	std::cout << a.StartsWith("bcd") << '\n';
	std::cout << a.StartsWith("bd") << '\n';
}

void SubStr()
{
	CTL::Dynamic::String a{ "abcdc" };

	LOGStr(a.SubStr(2, 4));
	LOGStr(a.SubStrC(2, 2));

	try
	{
		LOGStr(a.SubStrS(2, 2));
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << '\n';
	}

	try
	{
		LOGStr(a.SubStrCS(2, 4));
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << '\n';
	}
}

void Swap()
{
	CTL::Dynamic::String a{ "Ahmed 5" };
	CTL::Dynamic::String b{ "55 A" };

	LOGStr(a);
	LOGStr(b);

	std::cout << "Swapped......\n";
	a.Swap(b);

	LOGStr(a);
	LOGStr(b);

	std::cout << "Swapped 2......\n";
	b.Swap(a);

	LOGStr(a);
	LOGStr(b);
}

void Title()
{
	CTL::Dynamic::String a{ "this is going to be a title string" };
	LOGStr(a.Title());
	LOGStr(a);
	LOGStr(a.ToTitle());
	LOGStr(a);
}

void ToLUU()
{
	CTL::Dynamic::String a{ "this is going to be a title string" };

	LOGStr(a.ToUpper());
	LOGStr(a.ToLower());
	LOGStr(a.Upper());
	LOGStr(a);
}

void GettersAndSetters()
{
	const CTL::Dynamic::String a{ "abcdc" };

	std::cout << "Char At Index 1: " << a.At(5) << '\n';
	std::cout << ".begin of string: " << a.begin() << '\n';
	std::cout << ".Data of string: " << a.Data() << '\n';
	std::cout << ".end of string: " << a.end() << '\n';
	std::cout << ".Length of string: " << a.Length() << '\n';
	std::cout << ".Capacity of string: " << a.Capacity() << '\n';
}

void Operators()
{
	CTL::Dynamic::String a{ "abcdc" };
	CTL::Dynamic::String b{ "cscba" };

	std::cout << "operator[2]: " << a[2] << '\n';
	std::cout << "(a = 'New Data'): " << (a = "New Data") << '\n';
	std::cout << "(a = std::move(b)): " << (a = std::move(b)) << '\n';
	std::cout << "(a *= 2): " << (a *= 2) << '\n';
	std::cout << "operator+'h': " << (a + 'h') << '\n';
	std::cout << "operator+'Test': " << (a + "Test") << '\n';
	std::cout << "operator*2: " << (a * 2) << '\n';
	std::cout << "operator==cscbacscba: " << (a == "cscbacscba") << '\n';
	std::cout << "operator!=cscbacscba: " << (a != "cscbacscba") << '\n';
	std::cout << "operator>a: " << (a > "a") << '\n';
	std::cout << "operator>A: " << (a > "A") << '\n';
	std::cout << "operator<a: " << (a < "a") << '\n';
	std::cout << "operator<A: " << (a < "A") << '\n';
	std::cout << "operator>=c: " << (a < "c") << '\n';
	std::cout << "operator>=b: " << (a < "b") << '\n';
	std::cout << "operator<=A: " << (a < "A") << '\n';
	std::cout << "operator<=B: " << (a < "B") << '\n';
	std::cout << "operator std::string(): " << (std::string)a << '\n';
	std::cout << "operator''_DS: " << "Hi"_DS << '\n';
}