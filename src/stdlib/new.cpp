#include <new.hpp>
#include <memory/Manager.hpp>

void* operator new(size_t size) {
	if (memory::Manager::ActiveManager == nullptr)
		return nullptr;

	return memory::Manager::ActiveManager->malloc(size);
}
void* operator new[](size_t size) {
	if (memory::Manager::ActiveManager == nullptr)
		return nullptr;

	return memory::Manager::ActiveManager->malloc(size);
}

void* operator new(size_t size, void* ptr) {
	return ptr;
}
void* operator new[](size_t size, void* ptr) {
	return ptr;
}

void operator delete(void* pointer) {
	if (memory::Manager::ActiveManager != nullptr)
		memory::Manager::ActiveManager->free(pointer);
}
void operator delete[](void* pointer) {
	if (memory::Manager::ActiveManager != nullptr)
		memory::Manager::ActiveManager->free(pointer);
}
