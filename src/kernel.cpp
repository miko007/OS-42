/**
 * OS/42
 *
 * a blast of an operating system (just kidding)
 *
 * @author Michael Ochmann<miko@massivedynamic.eu>
 * @version 0.0.1
 */

#define __VERSION__ "0.0.1-2"

#include <types.hpp>
#include <iostream.hpp>
#include <memory/GlobalDescriptorTable.hpp>
#include <memory/Manager.hpp>
#include <interrupts/InterruptManager.hpp>
#include <drivers/Keyboard.hpp>
#include <drivers/Mouse.hpp>
#include <drivers/DriverManager.hpp>
#include <string.hpp>
#include <stdlib/new.hpp>
#include <stdlib/vector.hpp>
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

	std::cout << "MikOsoft OS/42 x86_32 " << __VERSION__ << " [" << __DATE__ << "] " << std::endl;
	std::cout << "(C) 2016, Michael Ochmann<miko@massivedynamic.eu>" << std::endl ;
	std::cout << "https://mike-ochmann.de" << std::endl << std::endl;
	std::cout << "[Boot]" << std::endl;
	std::cout << "loading tables" << std::endl;
	memory::GDT gdt;
	size_t heapStart = MB(10);
	uint32_t* heapLength = (uint32_t*) (((size_t) multibootStruct) + 8);
	memory::Manager memoryManager(heapStart, (*heapLength) * 1024 - heapStart - 10 * 1024);
	/**
	 * From here on, `operator new` is available
	 */
	auto interruptMgr = new interrupts::InterruptManager(0x20, &gdt);
/*
	std::string test = "abcde";
	std::string test2;

	test2 = "abcdef";
	std::cout << test2 << std::endl;
	test2 = "0123456789abcdef";
	test2.replace('a', '(');
	std::cout << test2 << std::endl;

	test.back() = '2';

	std::decimal c = std::decimal(strlen(test.c_str()));
	std::cout << test.back() <<  c << std::endl;*/

	auto driverMgr = new drivers::DriverManager();
	std::cout << "\t- KEYBOARD";
	auto keyboard = new drivers::Keyboard(interruptMgr);
	driverMgr->add(keyboard);
	std::cout << "\tMOUSE" << std::endl;
	auto mouse = new drivers::Mouse(interruptMgr);
	driverMgr->add(mouse);

	auto pciController = new hardware::PCIController();
	pciController->selectDrivers(driverMgr);

	driverMgr->activate();

	std::cout << "activating interrupts...";
	interruptMgr->activate();
	std::cout << "\tDONE!" << std::endl << std::endl;

	while(true);
}