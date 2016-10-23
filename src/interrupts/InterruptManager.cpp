//
// Created by miko on 23.10.16.
//

#include <interrupts/InterruptManager.hpp>
#include <iostream.hpp>
#include <string.hpp>
#include <interrupts/InterruptHandler.hpp>

namespace interrupts {

	InterruptManager::GateDescriptor InterruptManager::InterruptDescriptorTable[256];
	InterruptManager* InterruptManager::CurrentInterruptManager = nullptr;
	//checked
	InterruptManager::InterruptManager(uint16_t hwInterruptOffset, memory::GDT *gdt) :
			hwInterruptOffset(hwInterruptOffset),
			picMCommand(0x20),
			picMData(0x21),
			picSCommand(0xA0),
			picSData(0xA1) {

		uint16_t codeSegment = gdt->codeSegmentOffset();
		const uint8_t IDTInterruptGate = 0xE;

		for (uint8_t i = 255; i > 0; --i)
			InterruptManager::SetIDTEntry(i, codeSegment, &InterruptManager::IgnoreRequest, 0, IDTInterruptGate);
		InterruptManager::SetIDTEntry(0, codeSegment, &InterruptManager::IgnoreRequest, 0, IDTInterruptGate);

		// timer interrupt
		InterruptManager::SetIDTEntry(0x20, codeSegment, &InterruptManager::HandleRequest0x00, 0, IDTInterruptGate);
		// keyboard interrupt
		InterruptManager::SetIDTEntry(0x21, codeSegment, &InterruptManager::HandleRequest0x01, 0, IDTInterruptGate);

		this->picMCommand.write(0x11);
		this->picSCommand.write(0x11);

		this->picMData.write(0x20);
		this->picSData.write(0x28);

		this->picMData.write(0x04);
		this->picSData.write(0x02);

		this->picMData.write(0x01);
		this->picSData.write(0x01);

		this->picMData.write(0x00);
		this->picSData.write(0x00);

		IDTPointer idt;
		idt.size = 256 * sizeof(GateDescriptor) - 1;
		idt.base = (uint32_t) InterruptManager::InterruptDescriptorTable;
		asm volatile("lidt %0" : : "m" (idt));
	}

	void InterruptManager::activate() {
		if (InterruptManager::CurrentInterruptManager != nullptr)
			InterruptManager::CurrentInterruptManager->deactivate();
		InterruptManager::CurrentInterruptManager = this;
		asm("sti");
	}

	void InterruptManager::deactivate() {
		if (InterruptManager::CurrentInterruptManager == this) {
			InterruptManager::CurrentInterruptManager = nullptr;
			asm("cli");
		}
	}

	uint32_t InterruptManager::HandleInterrupt(uint8_t number, uint32_t esp) {
		if (InterruptManager::CurrentInterruptManager != nullptr)
			return InterruptManager::CurrentInterruptManager->processIterrupt(number, esp);

		return esp;
	}

	uint32_t InterruptManager::processIterrupt(uint8_t number, uint32_t esp) {
		if (this->handlers[number] != nullptr) {
			this->handlers[number]->handleInterrupt(esp);
		}
		/**
		 * ignore TIMER INTERRUPT
		 */
		else if (number != 0x20)
			std::cout << " > UNHANDLED Interrupt at address " << number << std::endl;

		if (number >= 0x20 && number <= 0x30) {
			this->picMCommand.write(0x20);
			if (number >= 0x28)
				this->picSCommand.write(0x20);
		}

		return esp;
	}

	//checked
	void InterruptManager::SetIDTEntry(uint8_t interruptNumber, uint16_t csSelectorOffset, void (*handler)(), uint8_t accessLevel, uint8_t flags) {
		const uint8_t IDTCurrentDesc = 0x80;

		InterruptManager::InterruptDescriptorTable[interruptNumber].handlerAddrLo = ((uint32_t) handler) & 0xFFFF;
		InterruptManager::InterruptDescriptorTable[interruptNumber].handlerAddrHi = (((uint32_t) handler) >> 16) & 0xFFFF;
		InterruptManager::InterruptDescriptorTable[interruptNumber].gdtCodeOffset = csSelectorOffset;
		InterruptManager::InterruptDescriptorTable[interruptNumber].access        = IDTCurrentDesc | flags | ((accessLevel & 3) << 5);
		InterruptManager::InterruptDescriptorTable[interruptNumber].reserved      = 0;
	}

}

