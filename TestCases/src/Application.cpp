#include <iostream>
#include <string>

#define PROFILING 1
#include "BenchCPP/Benchcpp17+.h"

#include "String/String.h"

void Test1()
{
	PROFILE_FUNCTION();

	CTL::Dynamic::String a{ "ahmed {}" };

	for (size_t i{}; i < 1'000'000; ++i)
	{
		a.SubStrC(0, 5);
	}
}

void Test2()
{
	PROFILE_FUNCTION();

	std::string a{ "ahmed {}" };

	for (size_t i{}; i < 1'000'000; ++i)
	{
		a.substr(0, 5);
	}
}

int main()
{
	funcsArray<void(*)()> funcs{ Test1, Test2 };
	
	START_PROFILE("TEST_1");
	Benchmarks::RunBenchmarks(funcs);
	END_PROFILE();
}