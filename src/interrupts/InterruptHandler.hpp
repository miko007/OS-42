//
// Created by miko on 23.10.16.
//

#pragma once

#include <types.hpp>
#include <interrupts/InterruptManager.hpp>

namespace interrupts {

	class InterruptHandler {
	protected:
		uint8_t number;
		InterruptManager* manager;
		InterruptHandler(uint8_t number, InterruptManager* manager) : number(number), manager(manager) {
			this->manager->handlers[this->number] = this;
		};
		~InterruptHandler() {
			if (this->manager->handlers[this->number] == this)
				this->manager->handlers[this->number] = nullptr;
		}
	public:
		virtual uint32_t handleInterrupt(uint32_t esp) {
			return esp;
		};
	};

}