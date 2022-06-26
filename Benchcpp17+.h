#pragma once

#include <vector>
#include <variant>

#include "BenchEngine.h"

template<typename ...T>
using funcsArray = std::vector<std::variant<T...>>;

namespace Benchmarks
{
    template<typename ...T>
    constexpr void RunBenchmarks(const funcsArray<T...>& funcs, const size_t& numberOfIterations = 1) {
        PROFILE_FUNCTION();
        COLISSION_DEFENDER();

        size_t temp{ numberOfIterations };
        for (auto& func : funcs)
        {
            for (; temp > 0; --temp)
                std::visit([](auto& fun) {fun(); }, func);

            temp = numberOfIterations;
        }
    }
}