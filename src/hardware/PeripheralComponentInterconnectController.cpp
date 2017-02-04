//
// Created by miko on 30.10.16.
//

#include <hardware/PeripheralComponentInterconnectController.hpp>
#include <iostream.hpp>

namespace hardware {

	PeripheralComponentInterconnectController::PeripheralComponentInterconnectController() :
			dataPort(0xCFC),
			commandPort(0xCF8) {}

	uint32_t PeripheralComponentInterconnectController::read(uint16_t bus, uint16_t device, uint16_t function, uint32_t offset) {
		uint32_t id = 0x1 << 31 | ((bus & 0xFF) << 16) | ((device & 0x1F) << 11) | ((function & 0x07) << 8) | (offset & 0xFC);
		this->commandPort.write(id);
		uint32_t response = this->dataPort.read();

		return response >> (8 * (offset % 4));
	}

	void PeripheralComponentInterconnectController::write(uint16_t bus, uint16_t device, uint16_t function, uint32_t offset, uint32_t value) {
		uint32_t id = 0x1 << 31 | ((bus & 0xFF) << 16) | ((device & 0x1F) << 11) | ((function & 0x07) << 8) | (offset & 0xFC);
		this->commandPort.write(id);
		this->dataPort.write(value);
	}

	bool PeripheralComponentInterconnectController::hasFunction(uint16_t bus, uint16_t device) {
		return this->read(bus, device, 0, 0x0E) & (1 << 7);
	}

	void PeripheralComponentInterconnectController::selectDrivers(drivers::DriverManager *driverMgr) {
		std::cout << "scanning for PCI devices..." << std::endl;
		for (int bus = 0; bus < 8; bus++) {
			for (int device = 0; device < 32; device++) {
				int functionCount = this->hasFunction(bus, device) ? 8 : 1;
				for (int function = 0; function < functionCount; function++) {
					PCIDeviceDescriptor deviceDescriptor(bus, device, function, this);
					if (deviceDescriptor.vendorID == 0x0000 || deviceDescriptor.vendorID == 0xFFFF)
						continue;
					std::cout << "\tBus: " << (uint8_t)(bus & 0xFF);
					std::cout << ", Device: " << (uint8_t) (device & 0xFF);
					std::cout << ", Function: " << (uint8_t) (function & 0xFF);
					std::cout << ", Vendor: " << (uint8_t) (deviceDescriptor.vendorID & 0xFF);
					std::cout << ", ID: " << (uint8_t) (deviceDescriptor.deviceID & 0xFF) << std::endl;
				}
			}
		}
		std::cout << "DONE!" << std::endl;
	}

	hardware::PCIDeviceDescriptor::PCIDeviceDescriptor(uint16_t bus, uint16_t device, uint16_t function, hardware::PeripheralComponentInterconnectController *pciC) :
			bus(bus), device(device), function(function), pciC(pciC) {
		this->vendorID = pciC->read(bus, device, function, 0x00);
		this->deviceID = pciC->read(bus, device, function, 0x02);
		this->classID = pciC->read(bus, device, function, 0x0B);
		this->subclassID = pciC->read(bus, device, function, 0x0A);
		this->interfaceID = pciC->read(bus, device, function, 0x09);
		this->revision = pciC->read(bus, device, function, 0x08);
		this->interrupt = pciC->read(bus, device, function, 0x3C);
	}

}

