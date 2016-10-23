//
// Created by miko on 23.10.16.
//

#include <drivers/Mouse.hpp>
#include <iostream.hpp>

namespace drivers {

	Mouse::Mouse(interrupts::InterruptManager *manager) :
			InterruptHandler(0x2C, manager),
			dataPort(0x60),
			commandPort(0x64),
			offset(0),
			buttons(0),
			screenBuffer((uint16_t*) 0xb8000),
			x(40),
			y(12){

		this->flip();
		/**
		 * tell the PIC to start sending mouse interrupts
		 */
		this->commandPort.write(0xA8);
		/**
		 * read the current state of the mouse
		 */
		this->commandPort.write(0x20);
		uint8_t state = this->dataPort.read() | 2;
		/**
		 * change keyboard state
		 */
		this->commandPort.write(0x60);
		this->dataPort.write(state);
		this->commandPort.write(0xD4);
		/**
		 * activate keyboard
		 */
		this->dataPort.write(0xF4);
		this->dataPort.read();
	}

	uint32_t Mouse::handleInterrupt(uint32_t esp) {
		uint8_t state = this->commandPort.read();
		if (!(state & 0x20))
			return esp;

		this->buffer[this->offset] = this->dataPort.read();
		this->offset = (this->offset + 1) % 3;
		if (this->offset == 0) {
			if(this->buffer[1] != 0 || this->buffer[2] != 0) {
				this->screenBuffer = (uint16_t*) 0xb8000;

				this->flip();

				this->x += this->buffer[1];
				this->x = this->x < 0 ? 0 : this->x;
				this->x = this->x >= 80 ? 79 : this->x;

				this->y -= this->buffer[2];
				this->y = this->y < 0 ? 0 : this->y;
				this->y = this->y >= 25 ? 24 : this->y;

				this->flip();

				for (uint8_t i = 0; i < 3; i++) {
					if (this->buffer[0] == 0x09)
					//if ((this->buffer[0] & (0x01 << i)) != this->buttons & (0x1 << i))
						this->flip();
				}

			}
			this->buttons = this->buffer[0];
		}

		return esp;
	}

	void Mouse::flip() {
		this->screenBuffer[80 * y +x] =   ((this->screenBuffer[80 * y + x] & 0xF000) >> 4)
										  | ((this->screenBuffer[80 * y + x] & 0x0F00) << 4)
										  |  (this->screenBuffer[80 * y + x] & 0x00FF);
	}


}

