#pragma once

#define _CTLBEGIN namespace CTL {
#define _CTLEND }

#define _DYNAMICBEGIN namespace Dynamic{
#define _DYNAMICEND }

// if C++20 or later is being used.
#if _MSVC_LANG >= 202002L

	#define CONSTEXPR20 constexpr
	#define Alloc(T, VAR, SIZE) VAR = new (std::nothrow) T[SIZE / sizeof(T)]
	#define AllocInit(T, VAR, SIZE) VAR = new (std::nothrow) T[SIZE / sizeof(T)]{}
	#define Dealloc(VAR) delete[] VAR; VAR = nullptr

#else

	#define CONSTEXPR20 inline
	#define Alloc(T, VAR, SIZE) VAR = static_cast<T*>(_malloca(SIZE)); _VerifyAlloc(VAR)
	#define AllocInit(T, VAR, SIZE) VAR = static_cast<T*>(_malloca(SIZE)); _VerifyAlloc(VAR); FillWItem(VAR, 0, SIZE / sizeof(T), T{})
	#define Dealloc(VAR) _freea(VAR); VAR = nullptr

#endif

#define _VerifyAlloc(VAR) if (!VAR) { throw std::bad_alloc(); }

#define NODISCARD17 [[nodiscard]]
#define FillWItem(VAR, START, END, CHARACTER) { size_t i{ START }; for(; i < END; ++i) VAR[i] = CHARACTER; }
#define FillWIterable(VAR, START, END, STRING) { size_t i{ START }; for(; i < END; ++i) VAR[i] = STRING[i]; }