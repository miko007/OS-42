//
// Created by miko on 23.10.16.
//

#pragma once

#include <types.hpp>
#include <hardware/Port.hpp>
#include <interrupts/InterruptHandler.hpp>
#include <drivers/Driver.hpp>

namespace interrupts {
	class InterruptManager;
}

namespace drivers {

	enum KeyCode {
		TOP1,
		TOP2,
		TOP3,
		TOP4,
		TOP5,
		TOP6,
		TOP7,
		TOP8,
		TOP9,
		TOP0,
		A,
		B,
		C,
		D,
		E,
		F,
		G,
		H,
		I,
		J,
		K,
		L,
		M,
		N,
		O,
		P,
		Q,
		R,
		S,
		T,
		U,
		V,
		W,
		X,
		Y,
		Z,
		SPACE,
		ENTER,
		COMMA,
		PERIOD,
		MINUS,
		BACKSPACE
	};

	class Keyboard : public interrupts::InterruptHandler, public drivers::Driver {
	private:
		hardware::Port<uint8_t> dataPort;
		hardware::Port<uint8_t> commandPort;
	public:
		Keyboard(interrupts::InterruptManager* manager);
		virtual uint32_t handleInterrupt(uint32_t esp);
		virtual void activate();
	};

}