//
// Created by miko on 22.10.16.
//

#include <memory/GlobalDescriptorTable.hpp>

namespace memory {

	GlobalDescriptorTable::GlobalDescriptorTable() :
			null(0, 0, 0),
			unused(0, 0, 0),
			code(0, 64 * 1024 * 1024, 0x9A),
			data(0, 64 * 1024 * 1024, 0x92) {

		uint32_t i[2];
		i[0] = (uint32_t) this;
		i[1] = sizeof(GlobalDescriptorTable) << 16;

		asm volatile("lgdt (%0)" : : "p" (((uint8_t *) i) + 2));
	}

	uint16_t GlobalDescriptorTable::codeSegmentOffset() {
		return (uint8_t*) & this->code - (uint8_t*) this;
	}

	uint16_t GlobalDescriptorTable::dataSegmentOffset() {
		return (uint8_t*) & this->data - (uint8_t*) this;
	}


	GlobalDescriptorTable::SegmentDescriptor::SegmentDescriptor(uint32_t base, uint32_t limit, uint8_t flags) {
		uint8_t* target = (uint8_t*) this;

		/**
		 * Encoding the `limit` of the Code Segment
		 */
		if (limit <= 65536)
			target[6] = 0x40;
		else {
			if ((limit & 0xFFF) != 0xFFF)
				limit = (limit & 0xFFF) - 1;
			else
				limit = limit >> 12;
			target[6] = 0xC0;
		}
		target[0] = limit & 0xFF;
		target[1] = (limit >> 8) & 0xFF;
		target[6] |= (limit >> 16) & 0xF;

		/**
		 * Encoding the `pointer` of the Code Segment
		 */
		target[2] = base & 0xFF;
		target[3] = (base >> 8) & 0xFF;
		target[4] = (base >> 16) & 0xFF;
		target[7] = (base >> 24) & 0xFF;

		target[5] = flags;
	}

	uint32_t GlobalDescriptorTable::SegmentDescriptor::base() {
		uint8_t* target = (uint8_t*) this;
		uint32_t result = target[7];
		result = (result << 8) + target[4];
		result = (result << 8) + target[3];
		result = (result << 8) + target[2];

		return result;
	}

	uint32_t GlobalDescriptorTable::SegmentDescriptor::limit() {
		uint8_t* target = (uint8_t*) this;
		uint32_t result = target[6] & 0xF;
		result = (result << 8) + target[1];
		result = (result << 8) + target[0];
		if ((target[6] & 0xC0) == 0xC0)
			result = (result << 12) | 0xFFF;

		return result;
	}

}

