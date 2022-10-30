#pragma once

#include <type_traits>

#ifndef _MSVC_LANG
#error _MSVC_LANG macro is required, please refer to https://docs.microsoft.com/en-us/cpp/preprocessor/predefined-macros?view=msvc-170
#endif

// if C++14 or earlier is being used.
#if _MSVC_LANG < 201703L
#error C++17 or later is required for CTL to function!
#endif

#define _CTLBEGIN namespace CTL {
#define _CTLEND }

#define _DYNAMICBEGIN namespace Dynamic{
#define _DYNAMICEND }

// if C++20 or later is being used.
#if _MSVC_LANG >= 202002L

	#define CONSTEXPR20 constexpr
	#define AllocIterable(T, VAR, SIZE) VAR = new (std::nothrow) T[SIZE / sizeof(T)]; _VerifyAlloc(VAR)
	#define AllocIterableInit(T, VAR, SIZE) VAR = new (std::nothrow) T[SIZE / sizeof(T)]{}; _VerifyAlloc(VAR)
	#define DeAlloc(VAR) delete[] VAR; VAR = nullptr

#else

	#define CONSTEXPR20 inline
	#define AllocIterable(T, VAR, SIZE) VAR = static_cast<T*>(_malloca(SIZE)); _VerifyAlloc(VAR)
	#define AllocIterableInit(T, VAR, SIZE) VAR = static_cast<T*>(_malloca(SIZE)); _VerifyAlloc(VAR); FillItem(VAR, 0, SIZE / sizeof(T), T{})
	#define DeAlloc(VAR) _freea(VAR); VAR = nullptr

#endif

#define _VerifyAlloc(VAR) if (!VAR) { throw std::bad_alloc(); }

#define NODISCARD17 [[nodiscard]]
#define FillItem(VAR, START, END, CHARACTER) { for(size_t i{ START }; i < END; ++i) VAR[i] = CHARACTER; }
#define CopyIterable(VAR, START, END, ITERABLE) { for(size_t i{ START }; i < END; ++i) VAR[i] = ITERABLE[i]; }
#define CopyIterableCustom(VAR, VAR_START, ITERABLE, ITERABLE_START, VAR_END, END) { for(size_t i{ VAR_START }, j{ ITERABLE_START }; VAR_END < END; ++j, ++i) VAR[i] = ITERABLE[j]; }

#define IsNum(INT) (47 < INT && INT < 58)
#define IsLowerCharacter(INT) (96 < INT && INT < 123)
#define IsUpperCharacter(INT) (64 < INT && INT < 91)
#define IsCharacter(INT) (IsLowerCharacter(INT) || IsUpperCharacter(INT))

template<typename T, typename... H>
struct IsAnyOf
{
	static constexpr bool value = ((std::is_same_v<T, H>) || ...);
};