/**
 * OS/42
 *
 * a blast of an operating system (just kidding)
 *
 * @author Michael Ochmann<miko@massivedynamic.eu>
 * @version 0.0.1
 */

#include <types.hpp>
#include <iostream.hpp>
#include "memory/gdt.h"
#include <hardware/Port.hpp>
#include <memory/GlobalDescriptorTable.hpp>
#include <interrupts/InterruptManager.hpp>

typedef void (*constructor)();
extern "C" constructor start_ctors;
extern "C" constructor end_ctors;
extern "C" void callConstructors() {
    for(constructor* i = &start_ctors; i != &end_ctors; i++)
        (*i)();
}


extern "C" void kernel(void* multibootStruct, uint32_t magicNumber) {
	std::cout << " > OS/42 --- v0.0.1" << std::endl;
	std::cout << " > booting..." << std::endl;


	memory::GlobalDescriptorTable gdt;
	interrupts::InterruptManager interruptMgr(0x20, &gdt);

	std::cout << " > activating interrupts..." << std::endl;
	interruptMgr.activate();
	std::cout << " > interrupts activated!" << std::endl;
	while(true);
}