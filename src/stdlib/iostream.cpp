//
// Created by miko on 22.10.16.
//

#include <iostream.hpp>
#include <string.hpp>

namespace std {
	const int ostream::TABSIZE = 4;

	ostream cout;
	NewLine endl;

	ostream::ostream() : outputBuffer(0), curX(0), curY(0) {}

	ostream& ostream::operator<<(const char *str) {
		this->outputBuffer = (uint16_t*) 0xb8000;
		for (int i = 0; str[i] != '\0'; ++i) {
			switch (str[i]) {
				case '\t':
					this->tab();
					break;
				case '\n':
					this->linefeed();
					break;
				default:
					this->place(str[i]);
					this->curX++;
					break;
			}
			if (this->curX >= 80) {
				this->linefeed();
			}
			/**
			 * Clear Buffer
			 */
			if (this->curY >= 25) {
				for (this->curY = 0; this->curY < 25; this->curY++) {
					for (this->curX = 0; this->curX < 80; this->curX++)
						this->place(' ');
				}
				this->curX = 0;
				this->curY = 0;
			}
		}

		return *this;
	}

	ostream &ostream::operator<<(uint8_t hex) {
		char* output = "0x00";
		const char* alphabet = "0123456789ABCDEF";
		output[2] = alphabet[(hex >> 4) & 0x0F];
		output[3] = alphabet[hex & 0x0F];
		cout << output;

		return *this;
	}

	ostream &ostream::operator<<(char car) {
		cout << &car;

		return *this;
	}

	ostream &ostream::operator<<(std::decimal integer) {

		uint8_t i = 9;
		uint8_t len = 0;
		std::decimal intbuf = integer;
		while (intbuf > 0) {
			char digit = (char) (intbuf % 10);
			//output[i] = digit + '0';
			intbuf /= 10;
			len++;
			i--;
		}
		i = 0;
		char output[10] = {};
		while (integer > 0) {
			char digit = (char) (integer % 10);
			output[len - i - 1] = digit + '0';
			integer /= 10;
			i++;
		}
		cout << output;

		return *this;
	}

	ostream &ostream::operator<<(std::string &string) {
		cout << string.c_str();

		return *this;
	}

	ostream &ostream::operator<<(const std::string &string) {
		cout << string.c_str();

		return *this;
	}

	ostream &ostream::operator<<(drivers::KeyCode key) {
		if (key == drivers::BACKSPACE) {
			this->remove();
			return *this;
		}
		const char* c;
		switch(key) {
			case drivers::TOP1: c = "1"; break;
			case drivers::TOP2: c = "2"; break;
			case drivers::TOP3: c = "3"; break;
			case drivers::TOP4: c = "4"; break;
			case drivers::TOP5: c = "5"; break;
			case drivers::TOP6: c = "6"; break;
			case drivers::TOP7: c = "7"; break;
			case drivers::TOP8: c = "8"; break;
			case drivers::TOP9: c = "9"; break;
			case drivers::TOP0: c = "0"; break;
			case drivers::A: c = "a"; break;
			case drivers::B: c = "b"; break;
			case drivers::C: c = "c"; break;
			case drivers::D: c = "d"; break;
			case drivers::E: c = "e"; break;
			case drivers::F: c = "f"; break;
			case drivers::G: c = "g"; break;
			case drivers::H: c = "h"; break;
			case drivers::I: c = "i"; break;
			case drivers::J: c = "j"; break;
			case drivers::K: c = "k"; break;
			case drivers::L: c = "l"; break;
			case drivers::M: c = "m"; break;
			case drivers::N: c = "n"; break;
			case drivers::O: c = "o"; break;
			case drivers::P: c = "p"; break;
			case drivers::Q: c = "q"; break;
			case drivers::R: c = "r"; break;
			case drivers::S: c = "s"; break;
			case drivers::T: c = "t"; break;
			case drivers::U: c = "u"; break;
			case drivers::V: c = "v"; break;
			case drivers::W: c = "w"; break;
			case drivers::X: c = "x"; break;
			case drivers::Y: c = "y"; break;
			case drivers::Z: c = "z"; break;
			case drivers::SPACE: c = " "; break;
			case drivers::ENTER: c = "\n"; break;
			case drivers::COMMA: c = ","; break;
			case drivers::PERIOD: c = "."; break;
			case drivers::MINUS: c = "-"; break;
			default:
				c = "";
				break;
		}
		cout << c;

		return *this;
	}

	ostream &ostream::operator<<(NewLine) {
		this->linefeed();

		return *this;
	}

	void ostream::place(const char c) {
		this->outputBuffer[80 * this->curY + this->curX] = (this->outputBuffer[80 * this->curY + this->curX] & 0xFF00) | c;
	}

	void ostream::linefeed() {
		this->curY++;
		this->curX = 0;
	}

	void ostream::tab() {
		for (int i = 0; i < ostream::TABSIZE; i++) {
			this->place(' ');
			this->curX++;
		}
	}

	void ostream::remove() {
		this->curX--;
		if (this->curX > 80) {
			this->curX = 80;
			this->curY--;
		}
		this->place(' ');
	}

}
