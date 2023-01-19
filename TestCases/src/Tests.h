#pragma once

#define LOGStr(VAR) PrintStr(VAR, __FUNCTION__, __LINE__)

#include "Iterables/Dynamic/String.h"

void PrintStr(const CTL::Dynamic::String& str, const char* funcName, int line);

void ConstructorsTest();
void AppendTest();
void CapitalizeTest();
void CountTest();
void EndsWithTest();
void FindTest();
void FormatTest();
void HasTest();
void IndexTest();
void InsertTest();
void IsSomethingTest();
void LowerTest();
void Reserve();
void Reset();
void Replace();
void Test8();
void Test9();
void Test10();
void Test11();
void Test12();
void Test13();