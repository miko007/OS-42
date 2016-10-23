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

typedef void (*constructor)();
extern "C" constructor start_ctors;
extern "C" constructor end_ctors;
extern "C" void callConstructors() {
    for(constructor* i = &start_ctors; i != &end_ctors; i++)
        (*i)();
}


extern "C" void kernel(void* multibootStruct, uint32_t magicNumber) {
	std::cout << "OS/42 x86_32 " << __VERSION__ << " [" << __DATE__ << "] " << std::endl;
	std::cout << "(C) 2016, Michael Ochmann<miko@massivedynamic.eu>" << std::endl ;
	std::cout << "https://mike-ochmann.de" << std::endl << std::endl;
	std::cout << "[Boot]" << std::endl;
	std::cout << "loading tables" << std::endl;

	memory::GDT gdt;
	interrupts::InterruptManager interruptMgr(0x20, &gdt);

	std::cout << "loading drivers" << std::endl;
	std::cout << "\t- KEYBOARD" << std::endl;
	drivers::Keyboard keyboard(&interruptMgr);
	std::cout << "\tDONE!" << std::endl;

	std::cout << "activating interrupts..." << std::endl;
	interruptMgr.activate();
	std::cout << "\tDONE!" << std::endl << std::endl;

	std::cout << "Welcome!" << std::endl;
	std::cout << "> _";

	while(true);
}