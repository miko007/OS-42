//
// Created by miko on 30.10.16.
//

#pragma once

#include <types.hpp>
#include <iostream.hpp>

namespace drivers {

	class Driver;

	class DriverManager {
	private:
		Driver* drivers[256];
		int driverCount;
	public:
		DriverManager() : driverCount(0) {
			std::cout << "loading drivers" << std::endl;
		}
		void add(Driver* driver) {
			this->drivers[this->driverCount] = driver;
			this->driverCount++;
		}
		void activate() {
			for (uint8_t i = 0; i < this->driverCount; i++) {
				this->drivers[i]->activate();
			}
			std::cout << "\tDONE!" << std::endl;
		}
	};

}