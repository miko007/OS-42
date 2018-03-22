#include <memory/Manager.hpp>
#include <iostream.hpp>
namespace memory {

	Manager* Manager::ActiveManager = nullptr;

	Manager::Manager(size_t start, size_t length) {
		Manager::ActiveManager = this;

		if (length < sizeof(Chunk))
			this->start = nullptr;
		else {
			this->start = (Chunk*) start;
			this->start->allocated = false;
			this->start->previous = nullptr;
			this->start->next = nullptr;
			this->start->size = length - sizeof(Chunk);
		}
	}

	Manager::~Manager() {
  		if (Manager::ActiveManager == this)
			Manager::ActiveManager = nullptr;
	}

	void* Manager::malloc(size_t size) {
		Chunk* found = nullptr;

		for (Chunk* chunk = this->start; chunk != nullptr && found == nullptr; chunk = chunk->next) {
			if (chunk->size > size && !chunk->allocated)
				found = chunk;
		}

		if (found == nullptr)
			return nullptr;

		if (found->size >= size + sizeof(Chunk) + 1) {
			Chunk* newChunk = (Chunk*) (((size_t) found) + sizeof(Chunk) + size);
			newChunk->allocated = false;
			newChunk->size = found->size - size - sizeof(Chunk);
			newChunk->previous = found;
			newChunk->next = found->next;
			if (newChunk->next != nullptr)
				newChunk->next->previous = newChunk;

			found->size = size;
			found->next = newChunk;
		}

		found->allocated = true;

		return (void*) (((size_t) found) + sizeof(Chunk));
	}

	void Manager::free(void *pointer) {
		Chunk* chunk = (Chunk*) ((size_t) pointer - sizeof(Chunk));
		chunk->allocated = false;

		if (chunk->previous != nullptr && !chunk->previous->allocated) {
			chunk->previous->next = chunk->next;
			chunk->previous->size += chunk->size + sizeof(Chunk);
			if (chunk->next != nullptr)
				chunk->next->previous = chunk->previous;
			chunk = chunk->previous;

			if (chunk->next != nullptr && !chunk->next->allocated) {
				chunk->size += chunk->next->size + sizeof(Chunk);
				chunk->next = chunk->next->next;
				if (chunk->next != nullptr)
					chunk->next->previous = chunk;
			}
		}
	}

}