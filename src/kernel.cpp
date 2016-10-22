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
#include <memory/GlobalDescriptorTable.hpp>
#include <hardware/Port.hpp>

extern "C" void kernel(void* multibootStruct, uint32_t magicNumber) {
	std::cout << " > OS/42 --- v0.0.1" << std::endl;
	std::cout << " > booting..." << std::endl;

	memory::GDT gdt;

	// testing if templates are working
	hardware::Port<uint16_t> port(15);
	port.write(0xFF0F);
	// end test

	while(true);
}