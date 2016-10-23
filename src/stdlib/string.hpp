//
// Created by miko on 23.10.16.
//

#pragma once

namespace std {

	char* strtoupper(const char* input) {
		char* str = "";
		for (uint8_t i = 0; input[i] != '\0'; ++i) {
			if (input[i] >= 97 && input[i] <= 122)
				str[i] = (input[i] & 0xFF00) | input[i] + 32;
			else
				str[i] = input[i];
		}

		return str;
	}

}