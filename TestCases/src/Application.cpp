#include <iostream>
#include "String/String.h"

#define PROFILING 1
#include "Benchcpp17+.h"

void Test1() noexcept
{
	PROFILE_FUNCTION();

	for (size_t i{}; i < 100'000; ++i)
	{
		{
			CustomSTL::String s{};
		}
	}
}

void Test2() noexcept
{
	PROFILE_FUNCTION();

	for (size_t i{}; i < 100'000; ++i)
	{
		{
			std::string s{};
		}
	}
}

int main()
{
	funcsArray<void(*)()> funcs{ Test1, Test2 };
	START_PROFILE("NEW");
	Benchmarks::RunBenchmarks(funcs);
	END_PROFILE();
}