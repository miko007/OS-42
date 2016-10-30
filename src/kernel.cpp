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
#include <interrupts/InterruptManager.hpp>
#include <drivers/Keyboard.hpp>
#include <drivers/Mouse.hpp>
#include <drivers/DriverManager.hpp>

typedef void (*constructor)();
extern "C" constructor start_ctors;
extern "C" constructor end_ctors;
extern "C" void callConstructors() {
    for(constructor* i = &start_ctors; i != &end_ctors; i++)
        (*i)();
}


extern "C" void kernel(void* multibootStruct, uint32_t magicNumber) {
	int a = 1200;
	std::cout << ":: " << a << std::endl;
	std::cout << "MikOsoft OS/42 x86_32 " << __VERSION__ << " [" << __DATE__ << "] " << std::endl;
	std::cout << "(C) 2016, Michael Ochmann<miko@massivedynamic.eu>" << std::endl ;
	std::cout << "https://mike-ochmann.de" << std::endl << std::endl;
	std::cout << "[Boot]" << std::endl;
	std::cout << "loading tables" << std::endl;
	std::cout << "\t- GLOBAL DESCRIPTOR TABLE" << std::endl;
	memory::GDT gdt;
	std::cout << "\t- INTERRUPT DESCRIPTOR TABLE" << std::endl;
	interrupts::InterruptManager interruptMgr(0x20, &gdt);

	drivers::DriverManager driverMgr;
	std::cout << "\t- KEYBOARD" << std::endl;
	drivers::Keyboard keyboard(&interruptMgr);
	driverMgr.add(&keyboard);
	std::cout << "\t- MOUSE" << std::endl;
	drivers::Mouse mouse(&interruptMgr);
	driverMgr.add(&mouse);

	driverMgr.activate();

	std::cout << "activating interrupts..." << std::endl;
	interruptMgr.activate();
	std::cout << "\tDONE!" << std::endl << std::endl;

	std::cout << "Welcome!" << std::endl;
	std::cout << "> _";

	while(true);
}