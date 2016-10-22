//
// Created by miko on 22.10.16.
//

#pragma once

#include "types.hpp"

int printf(const char* str) {
	uint16_t* videoMemory = (uint16_t*) 0xb8000;
	int i;
	for (i = 0; str[i] != '\0'; ++i)
		videoMemory[i] = (videoMemory[i] & 0xFF00) | str[i];
	return i;
}