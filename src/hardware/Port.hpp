//
// Created by miko on 22.10.16.
//

#pragma once

#include <types.hpp>

namespace hardware {

	template <typename T>
	class Port {
	protected:
		uint16_t portnumber;
	public:
		Port(uint16_t portnumber) : portnumber(portnumber) {}
		virtual void write(T data) {
			if (sizeof(T) == sizeof(uint16_t))
				__asm__ volatile("outw %0, %1" : : "a" (data), "Nd" (this->portnumber));
			else if (sizeof(T) == sizeof(uint32_t))
				__asm__ volatile("outl %0, %1" : : "a" (data), "Nd" (this->portnumber));
			else
				__asm__ volatile("outb %0, %1" : : "a" (data), "Nd" (this->portnumber));
		}

		T read() {
			T result;
			if (sizeof(T) == sizeof(uint16_t))
				__asm__ volatile("inw %1, %0" : "=a" (result) : "Nd" (this->portnumber));
			else if (sizeof(T) == sizeof(uint32_t))
				__asm__ volatile("inl %1, %0" : "=a" (result) : "Nd" (this->portnumber));
			else
				__asm__ volatile("inb %1, %0" : "=a" (result) : "Nd" (this->portnumber));

			return result;
		}
	};

	class PortSlow : public Port<uint8_t> {
	public:
		PortSlow(uint16_t portnumber) : Port(portnumber) {};
		virtual void write(uint8_t data) {
			__asm__ volatile("outb %0, %1\njmp 1f\n1:" : : "a" (data), "Nd" (this->portnumber));
		};
	};

}
