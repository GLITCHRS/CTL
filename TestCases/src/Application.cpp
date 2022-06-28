#include <iostream>
#include <format>
#include "String/String.h"

#define PROFILING 1
#include "Benchcpp17+.h"

void Test1() noexcept
{
	PROFILE_FUNCTION();

	CTL::String s{" LOLDataLOL "};

	for (size_t i{}; i < 1000'000; ++i)
	{
		if(s.Has(std::format("{}", i)));
	}
}

void Test2() noexcept
{
	PROFILE_FUNCTION();

	std::string s{ "LOLDataLOL" };

	for (size_t i{}; i < 1000'000; ++i)
	{
		if (s.find(std::format("{}", i)) != std::string::npos);
	}
}

int main()
{
	funcsArray<void(*)()> funcs{ Test1, Test2 };
	START_PROFILE("NEW");
	Benchmarks::RunBenchmarks(funcs);
	END_PROFILE();
}