#pragma once

#define _CTLBEGIN namespace CTL {
#define _CTLEND }

#define _DYNAMICBEGIN namespace Dynamic{
#define _DYNAMICEND }

// if C++20 or later is being used.
#if _MSVC_LANG >= 202002L

	#define CONSTEXPR20 constexpr
	#define AllocIterable(T, VAR, SIZE) VAR = new (std::nothrow) T[SIZE / sizeof(T)]; _VerifyAlloc(VAR)
	#define AllocIterableInit(T, VAR, SIZE) VAR = new (std::nothrow) T[SIZE / sizeof(T)]{}; _VerifyAlloc(VAR)
	#define Dealloc(VAR) delete[] VAR; VAR = nullptr

#else

	#define CONSTEXPR20 inline
	#define AllocIterable(T, VAR, SIZE) VAR = static_cast<T*>(_malloca(SIZE)); _VerifyAlloc(VAR)
	#define AllocIterableInit(T, VAR, SIZE) VAR = static_cast<T*>(_malloca(SIZE)); _VerifyAlloc(VAR); FillWItem(VAR, 0, SIZE / sizeof(T), T{})
	#define Dealloc(VAR) _freea(VAR); VAR = nullptr

#endif

#define _VerifyAlloc(VAR) if (!VAR) { throw std::bad_alloc(); }

#define NODISCARD17 [[nodiscard]]
#define FillWItem(VAR, START, END, CHARACTER) { for(size_t i{ START }; i < END; ++i) VAR[i] = CHARACTER; }
#define FillWIterable(VAR, START, END, ITERABLE) { for(size_t i{ START }; i < END; ++i) VAR[i] = ITERABLE[i]; }
#define FillWIterableCustom(VAR, VAR_START, ITERABLE, ITERABLE_START, VAR_END, END) { for(size_t i{ VAR_START }, j{ ITERABLE_START }; VAR_END < END; ++j, ++i) VAR[i] = ITERABLE[j]; }
