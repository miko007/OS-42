//
// Created by miko on 22.10.16.
//

#include <iostream.hpp>

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
			if (this->curY >= 25) {
				for (this->curY = 0; this->curY < 25; this->curY++) {
					for (this->curX = 0; this->curX < 80; this->curX++)
						this->place(' ');
				}
			}
		}

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

}
