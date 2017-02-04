/**
 * OS/42
 *
 * a blast of an operating system (just kidding)
 *
 * @author Michael Ochmann<miko@massivedynamic.eu>
 * @version 0.0.1
 */

#define __VERSION__ "0.0.1"

#include <types.hpp>
#include <iostream.hpp>
#include <memory/GlobalDescriptorTable.hpp>
#include <memory/Manager.hpp>
#include <interrupts/InterruptManager.hpp>
#include <drivers/Keyboard.hpp>
#include <drivers/Mouse.hpp>
#include <drivers/DriverManager.hpp>
#include <hardware/PeripheralComponentInterconnectController.hpp>

typedef void (*constructor)();
extern "C" constructor start_ctors;
extern "C" constructor end_ctors;
extern "C" void callConstructors() {
    for(constructor* i = &start_ctors; i != &end_ctors; i++)
        (*i)();
}


extern "C" void kernel(void* multibootStruct, uint32_t magicNumber) {
	int a = 5;
	int b = 3;
	std::decimal c = std::decimal(a+b+10000);
	std::cout << ":: " << c << std::endl;
	std::cout << "MikOsoft OS/42 x86_32 " << __VERSION__ << " [" << __DATE__ << "] " << std::endl;
	std::cout << "(C) 2016, Michael Ochmann<miko@massivedynamic.eu>" << std::endl ;
	std::cout << "https://mike-ochmann.de" << std::endl << std::endl;
	std::cout << "[Boot]" << std::endl;
	std::cout << "loading tables" << std::endl;
	memory::GDT gdt;
	size_t heapStart = MB(10);
	uint32_t* heapLength = (uint32_t*) (((size_t) multibootStruct) + 8);
	memory::Manager memoryManager(heapStart, (*heapLength) * 1024 - heapStart - 10 * 1024);
	interrupts::InterruptManager interruptMgr(0x20, &gdt);

	drivers::DriverManager driverMgr;
	std::cout << "\t- KEYBOARD";
	drivers::Keyboard keyboard(&interruptMgr);
	driverMgr.add(&keyboard);
	std::cout << "\tMOUSE" << std::endl;
	drivers::Mouse mouse(&interruptMgr);
	driverMgr.add(&mouse);

	hardware::PCIController* pciController = new hardware::PCIController();
	pciController->selectDrivers(&driverMgr);

	driverMgr.activate();

	std::cout << "activating interrupts...";
	interruptMgr.activate();
	std::cout << "\tDONE!" << std::endl << std::endl;

	while(true);
}