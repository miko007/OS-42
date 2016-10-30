//
// Created by miko on 30.10.16.
//

#include <hardware/PeripheralComponentInterconnectController.hpp>

namespace hardware {

	PeripheralComponentInterconnectController::PeripheralComponentInterconnectController() :
			dataPort(0xCFC),
			commandPort(0xCF8) {}

	uint32_t PeripheralComponentInterconnectController::read(uint16_t bus, uint16_t device, uint16_t function, uint32_t offset) {
		
	}

	void PeripheralComponentInterconnectController::write(uint16_t bus, uint16_t device, uint16_t function, uint32_t offset, uint32_t value) {

	}

}

