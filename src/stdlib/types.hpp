//
// Created by miko on 22.10.16.
//

#pragma once

#define null 0
#define nullptr null
#define MB(X) (X * 1024 * 1024)

typedef char int8_t;
typedef unsigned char uint8_t;
typedef short int16_t;
typedef unsigned short uint16_t;
typedef int int32_t;
typedef unsigned int uint32_t;
typedef long long int64_t;
typedef unsigned long long uint64_t;
typedef uint32_t size_t;

typedef uint32_t size_t;

namespace std {
	class decimal {
	public:
		constexpr explicit decimal(int value) : value(value) {};
		constexpr operator int() const noexcept {
			return this->value;
		};
		int operator/= (int value) {
			this->value = this->value / value;
			return this->value;
		};
	private:
		int value;
	};
}

constexpr std::decimal operator"" d(uint64_t value) {
	return std::decimal(value);
}