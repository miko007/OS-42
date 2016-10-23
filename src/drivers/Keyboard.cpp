//
// Created by miko on 23.10.16.
//

#include <drivers/Keyboard.hpp>
#include <iostream.hpp>

namespace drivers {
	
	Keyboard::Keyboard(interrupts::InterruptManager *manager) :
			InterruptHandler(0x21, manager),
			dataPort(0x60),
			commandPort(0x64){

		while(this->commandPort.read() & 0x1)
			this->dataPort.read();
		/**
		 * tell the PIC to start sending keyboard interrupts
		 */
		this->commandPort.write(0xAE);
		/**
		 * read the current state of the keyboard
		 */
		this->commandPort.write(0x20);
		uint8_t state = (this->dataPort.read() | 1) & ~0x10;
		/**
		 * change keyboard state
		 */
		this->commandPort.write(0x60);
		this->dataPort.write(state);
		/**
		 * activate keyboard
		 */
		this->dataPort.write(0xF4);
	}

	uint32_t Keyboard::handleInterrupt(uint32_t esp) {
		uint8_t keyCode = this->dataPort.read();

		/**
		 * ignore keyUp interrupt for now
		 */
		if (keyCode > 0x80)
			return esp;

		KeyCode pressed;
		switch (keyCode) {
			case 0x45:
			case 0xC5:
			case 0xFA:
				break;
			case 0x02: pressed = TOP1; break;
			case 0x03: pressed = TOP2; break;
			case 0x04: pressed = TOP3; break;
			case 0x05: pressed = TOP4; break;
			case 0x06: pressed = TOP5; break;
			case 0x07: pressed = TOP6; break;
			case 0x08: pressed = TOP7; break;
			case 0x09: pressed = TOP8; break;
			case 0x0A: pressed = TOP9; break;
			case 0x0B: pressed = TOP0; break;

			case 0x10: pressed = Q; break;
			case 0x11: pressed = W; break;
			case 0x12: pressed = E; break;
			case 0x13: pressed = R; break;
			case 0x14: pressed = T; break;
			case 0x15: pressed = Z; break;
			case 0x16: pressed = U; break;
			case 0x17: pressed = I; break;
			case 0x18: pressed = O; break;
			case 0x19: pressed = P; break;

			case 0x1E: pressed = A; break;
			case 0x1F: pressed = S; break;
			case 0x20: pressed = D; break;
			case 0x21: pressed = F; break;
			case 0x22: pressed = G; break;
			case 0x23: pressed = H; break;
			case 0x24: pressed = J; break;
			case 0x25: pressed = K; break;
			case 0x26: pressed = L; break;

			case 0x2C: pressed = Y; break;
			case 0x2D: pressed = X; break;
			case 0x2E: pressed = C; break;
			case 0x2F: pressed = V; break;
			case 0x30: pressed = B; break;
			case 0x31: pressed = N; break;
			case 0x32: pressed = M; break;
			case 0x33: pressed = COMMA; break;
			case 0x34: pressed = PERIOD; break;
			case 0x35: pressed = MINUS; break;

			case 0x1C: pressed = ENTER; break;
			case 0x39: pressed = SPACE; break;
			case 0x0E: pressed = BACKSPACE; break;
			default:
				std::cout << "unregistered Keypress with keyCode " << keyCode << std::endl;
				break;
		}
		std::cout << pressed;

		return esp;
	}
}