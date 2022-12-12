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
	#define AllocIterable(T, VAR, LENGTH) VAR = new (std::nothrow) T[LENGTH]; _VerifyPointer(VAR)
	#define AllocIterableInit(T, VAR, LENGTH) VAR = new (std::nothrow) T[LENGTH]{}; _VerifyPointer(VAR)
	#define DeAlloc(VAR) delete[] VAR; VAR = nullptr

#else

	#define CONSTEXPR20 inline
	#define AllocIterable(T, VAR, LENGTH) VAR = static_cast<T*>(_malloca((LENGTH) * sizeof(T))); _VerifyPointer(VAR)
	#define AllocIterableInit(T, VAR, LENGTH) VAR = static_cast<T*>(_malloca(LENGTH * sizeof(T))); _VerifyPointer(VAR); FillIterable(VAR, 0, LENGTH, T{})
	#define DeAlloc(VAR) _freea(VAR); VAR = nullptr

#endif

#define _VerifyPointer(VAR) if (!VAR) { throw std::bad_alloc(); }

#define NODISCARD17 [[nodiscard]]
#define FillIterable(VAR, START, END, CHARACTER) { for(size_t i{ START }; i < END; ++i) VAR[i] = CHARACTER; }
#define CopyIterable(VAR, START, END, ITERABLE) { for(size_t i{ START }; i < END; ++i) VAR[i] = ITERABLE[i]; }
#define CopyIterableInit(T, VAR, START, END, NEW_LENGTH, ITERABLE) CopyIterable(VAR, START, END, ITERABLE); FillIterable(VAR, END, NEW_LENGTH, T{})
#define ReAllocIterable(T, VAR, OLD_LENGTH, NEW_LENGTH) { T* tempBuffer{ VAR }; AllocIterable(T, VAR, (NEW_LENGTH)); CopyIterable(VAR, 0, OLD_LENGTH, tempBuffer); DeAlloc(tempBuffer); }
#define ReAllocIterableInit(T, VAR, OLD_LENGTH, NEW_LENGTH) { T* tempBuffer{ VAR }; AllocIterable(T, VAR, NEW_LENGTH); CopyIterable(VAR, 0, OLD_LENGTH, tempBuffer); FillIterable(VAR, OLD_LENGTH, NEW_LENGTH, T{}); VAR[NEW_LENGTH] = T{}; DeAlloc(tempBuffer); }

#define ShiftToLeft(VAR, START, END, STEPS) { for(size_t i{ START }; i < END; ++i) VAR[i - STEPS] = VAR[i]; }
#define ShiftToRight(VAR, START, END, STEPS) { size_t i{ END }; while(i > START) VAR[i + STEPS] = VAR[--i]; }

#define IsNum(INT) (47 < INT && INT < 58)
#define IsLowerChar(INT) (96 < INT && INT < 123)
#define IsUpperChar(INT) (64 < INT && INT < 91)
#define IsChar(INT) (IsLowerChar(INT) || IsUpperChar(INT))
#define IsSpace(INT) (INT == 32 || INT == 10 || INT == 9)

template<typename T, typename... H>
struct IsAnyOf
{
	static constexpr bool value = ((std::is_same_v<T, H>) || ...);
};