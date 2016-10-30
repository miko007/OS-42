//
// Created by miko on 30.10.16.
//

#pragma once

#include <types.hpp>
#include <hardware/Port.hpp>

namespace hardware {

	class PeripheralComponentInterconnectController {
	private:
		Port<uint32_t> dataPort;
		Port<uint32_t> commandPort;
	public:
		PeripheralComponentInterconnectController();
		uint32_t read(uint16_t bus, uint16_t device, uint16_t function, uint32_t offset);
		void write(uint16_t bus, uint16_t device, uint16_t function, uint32_t offset, uint32_t value);

	};

	typedef PeripheralComponentInterconnectController PCI;

}
