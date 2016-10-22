//
// Created by miko on 22.10.16.
//

#include <iostream.hpp>

namespace std {
	iostream cout;
	char* endl = (char*) '\n';

	iostream::iostream() {}

	iostream& iostream::operator<<(const char *str) {
		uint16_t* outputBuffer = (uint16_t*) 0xb8000;
		int i;
		for (i = 0; str[i] != '\0'; ++i)
			outputBuffer[i] = (outputBuffer[i] & 0xFF00) | str[i];
		return *this;
	}
}
