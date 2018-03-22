#pragma once

#include <types.hpp>

void* operator new(size_t size);
void* operator new[](size_t size);

void* operator new(size_t size, void* ptr);
void* operator new[](size_t size, void* ptr);

void operator delete(void* pointer);
void operator delete[](void* pointer);