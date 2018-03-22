#pragma once

#include <types.hpp>
#include <new.hpp>
#include <memory/Manager.hpp>

#define VECTOR_DEFAULT_LENGTH 10

namespace std {

	template <typename T>
	class vector {
	private:
		T* elements;
		size_t bufferSize;
		size_t count;
	public:
		vector() :
				elements(new char[VECTOR_DEFAULT_LENGTH * sizeof(T)]), count(0),
				bufferSize(VECTOR_DEFAULT_LENGTH * sizeof(T)) {};
		void emplace_back(T item) {
			this->elements[this->count] = static_cast<T*>(new T(item));
			this->count++;
		}


		size_t size() {
			return this->count;
		}
	};

}