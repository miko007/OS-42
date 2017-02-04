//
// Created by miko on 30.10.16.
//

#pragma once

#include <types.hpp>
#include <hardware/Port.hpp>
#include <drivers/Driver.hpp>

namespace drivers {
	class DriverManager;
}

namespace hardware {

	class PeripheralComponentInterconnectController;

	struct PCIDeviceDescriptor {
		PeripheralComponentInterconnectController* pciC;
		uint32_t port;
		uint32_t interrupt;

		uint16_t bus;
		uint16_t device;
		uint16_t function;
		uint16_t vendorID;
		uint16_t deviceID;

		uint8_t classID;
		uint8_t subclassID;
		uint8_t interfaceID;
		uint8_t revision;

		PCIDeviceDescriptor(uint16_t bus, uint16_t device, uint16_t function, PeripheralComponentInterconnectController* pciC);
	};

	class PeripheralComponentInterconnectController {
	private:
		Port<uint32_t> dataPort;
		Port<uint32_t> commandPort;
	public:
		PeripheralComponentInterconnectController();
		uint32_t read(uint16_t bus, uint16_t device, uint16_t function, uint32_t offset);
		void write(uint16_t bus, uint16_t device, uint16_t function, uint32_t offset, uint32_t value);
		bool hasFunction(uint16_t bus, uint16_t device);
		void selectDrivers(drivers::DriverManager* driverMgr);
	};

	typedef PeripheralComponentInterconnectController PCIController;

}
