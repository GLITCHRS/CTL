#include <iostream>
#include "String/String.h"

#define PROFILING 1
#include "Benchcpp17+.h"

void Test1() noexcept
{
	CustomSTL::String s{};
}

int main()
{
	funcsArray<void(*)()> funcs{ Test1 };
	START_PROFILE("TEST1");
	Benchmarks::RunBenchmarks(funcs, 100);
	END_PROFILE();
}