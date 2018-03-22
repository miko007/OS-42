#pragma once

#include <types.hpp>

namespace memory {

	struct Chunk {
		Chunk* next;
		Chunk* previous;
		bool allocated;
		size_t size;
	};

	class Manager {
	private:
		Chunk* start;
	public:
		static Manager* ActiveManager;
		Manager(size_t start, size_t length);
		~Manager();
		void* malloc(size_t size);
		void free(void* pointer);
	};

}