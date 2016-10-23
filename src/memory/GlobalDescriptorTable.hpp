//
// Created by miko on 22.10.16.
//

#pragma once

#include <types.hpp>

namespace memory {

	class GlobalDescriptorTable {
	public:
		GlobalDescriptorTable();
		uint16_t codeSegmentOffset();
		uint16_t dataSegmentOffset();
		class SegmentDescriptor {
		private:
			uint16_t limitLo;
			uint16_t baseLo;
			uint8_t baseHi;
			uint8_t type;
			uint8_t flagsLimitHi;
			uint8_t baseVHi;
		public:
			SegmentDescriptor(uint32_t base, uint32_t limit, uint8_t flags);
			uint32_t base();
			uint32_t limit();
		} __attribute__((packed));
	private:
		SegmentDescriptor nullSegm;
		SegmentDescriptor unusedSegm;
		SegmentDescriptor codeSegm;
		SegmentDescriptor dataSegm;
	};

	typedef GlobalDescriptorTable GDT;
}