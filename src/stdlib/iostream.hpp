//
// Created by miko on 22.10.16.
//

#pragma once

#include <types.hpp>

namespace std {

	class NewLine{};

	class ostream {
	private:
		static const int TABSIZE;

		uint16_t* outputBuffer;
		uint8_t curX;
		uint8_t curY;
		void place(const char c);
		void linefeed();
		void tab();
	public:
		ostream();
		ostream& operator<<(const char* str);
		ostream& operator<<(NewLine);
	};

	extern ostream cout;
	extern NewLine endl;

}