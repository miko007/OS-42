//
// Created by miko on 23.10.16.
//

#pragma once

#include <interrupts/InterruptHandler.hpp>
#include <hardware/Port.hpp>
#include <types.hpp>
#include <drivers/Driver.hpp>

namespace interrupts {
	class InterruptManager;
}

namespace drivers {

	class Mouse : public interrupts::InterruptHandler, public drivers::Driver {
	private:
		hardware::Port<uint8_t> dataPort;
		hardware::Port<uint8_t> commandPort;
		uint8_t buffer[3];
		uint8_t offset;
		uint8_t buttons;
		uint16_t* screenBuffer;
		int8_t x;
		int8_t y;
		void flip();
	public:
		Mouse(interrupts::InterruptManager* manager);
		virtual uint32_t handleInterrupt(uint32_t esp);
		virtual void activate();
	};

}