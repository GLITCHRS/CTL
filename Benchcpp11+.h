#pragma once

#include <vector>
#include <variant>

#include "BenchEngine.h"

template<typename ...T>
using funcsArray = std::vector<std::variant<T...>>;

namespace Benchmarks
{
    template<typename ...T>
    static inline constexpr void RunBenchmarks(const funcsArray<T...>& funcs, size_t&& numberOfIterations) {
        PROFILE_FUNCTION();
        COLISSION_DEFENDER();
        const size_t temp{ numberOfIterations };
        for (auto& func : funcs)
        {
            for (; numberOfIterations > 0; --numberOfIterations)
            {
                std::visit([](auto& fun) {fun(); }, func);
            }
            numberOfIterations = temp;
        }
    }
    template<typename ...T>
    static inline constexpr void RunBenchmarks(const funcsArray<T...>& args, size_t&& numberOfIterations = 1);
}