//
// Created by miko on 22.10.16.
//

#pragma once

#include <types.hpp>
#include <drivers/Keyboard.hpp>

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
		void remove();
	public:
		ostream();
		ostream& operator<<(const char* str);
		ostream& operator<<(uint8_t hex);
		/**
		 * Until we have a shell, this is how we get input on the screen
		 */
		ostream& operator<<(drivers::KeyCode key);
		ostream& operator<<(NewLine);
	};

	extern ostream cout;
	extern NewLine endl;

}