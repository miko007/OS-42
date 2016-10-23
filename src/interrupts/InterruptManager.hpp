//
// Created by miko on 23.10.16.
//

#pragma once

#include <types.hpp>
#include <hardware/Port.hpp>
#include "../memory/gdt.h"
#include <memory/GlobalDescriptorTable.hpp>

namespace interrupts {

	class InterruptManager {
	protected:
		struct GateDescriptor {
			uint16_t handlerAddrLo;
			uint16_t gdtCodeOffset;
			uint8_t reserved;
			uint8_t access;
			uint16_t handlerAddrHi;
		}__attribute__((packed));
		static GateDescriptor InterruptDescriptorTable[256];

		struct IDTPointer {
			uint16_t size;
			uint32_t base;
		}__attribute__((packed));

		uint16_t hwInterruptOffset;
		hardware::PortSlow picMCommand;
		hardware::PortSlow picMData;
		hardware::PortSlow picSCommand;
		hardware::PortSlow picSData;

		static void SetIDTEntry(uint8_t interruptNumber, uint16_t csSelectorOffset, void (*handler)(), uint8_t accessLevel, uint8_t flags);

		static void IgnoreRequest();
		static void ExceptionRequest();

		static void HandleRequest0x00();
		static void HandleRequest0x01();

		static uint32_t HandleInterrupt(uint8_t number, uint32_t esp);
	public:
		InterruptManager(uint16_t hwInterruptOffset, memory::GlobalDescriptorTable* gdt);
		void activate();
	};

}

