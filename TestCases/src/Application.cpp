#include <iostream>
#include "String/String.h"

#define PROFILING 0
#include "Benchcpp11+.h"

void Test1()
{
	CustomSTL::String name{ "Hello W Worl World" };

	for (size_t i{}; i < 1'000'000; ++i)
		name.Has("World");
}

int main()
{
	funcsArray<void(*)()> funcs{ Test1 };
	START_PROFILE("TEST1");
	Benchmarks::RunBenchmarks(funcs);
	END_PROFILE();
}