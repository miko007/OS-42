#pragma once

#define STRING_DEFAULT_LENGTH 15

#include <iostream.hpp>
#include <new.hpp>

inline void* memset(void* start, uint8_t byte, size_t length) {
	uint8_t* pointer = (uint8_t*) start;
	while (length--)
		*pointer++ = (uint8_t) byte;

	return start;
}

inline void* memcpy(void* destination, const void* source, size_t length) {
	char* dest = (char*) destination;
	const char* src = (const char*) source;
	for (size_t i = 0; i < length; i++)
		dest[i] = src[i];

	return destination;
}

inline char* strtoupper(const char* input) {
	char* str = "";
	for (uint8_t i = 0; input[i] != '\0'; ++i) {
		if (input[i] >= 97 && input[i] <= 122)
			str[i] = (input[i] & 0xFF00) | input[i] + 32;
		else
			str[i] = input[i];
	}

	return str;
}

inline size_t strlen(const char* string) {
	size_t length = 0;
	while(*string++ != '\0')
		length++;

	return (size_t) length;
}

namespace std {

	class string {
	private:
		size_t len;
		uint32_t bufferSize;
		char* content;

		bool reset(char* str) {
			size_t len = strlen(str);
			if (len > this->bufferSize)
				return false;
			memcpy(this->content, str, len);
			memset(this->content + len, 0, this->bufferSize - len);
			this->len = len;

			return true;
		}
	public:
		string(size_t length = STRING_DEFAULT_LENGTH) :
				content(new char[length]), len(0), bufferSize(length) {
			memset(this->content, 0, length);
		}
		string(const char* string) {
			size_t length    = strlen(string) + 1;
			this->content    = new char[length];
			this->len        = length - 1;
			this->bufferSize = length;
			memcpy(this->content, string, length);
		}
		string(const string& string) :
				content(new char[string.len]), len(string.len),
				bufferSize(string.bufferSize){
			memcpy(this->content, string.c_str() - 1, string.len);
		}
		~string() {
			if (this->content)
				delete[] this->content;
		}
		size_t size() const {
			return this->len;
		}
		size_t length() const {
			return this->size();
		}

		char& at(size_t position) {
			//if (position < 0 || position > this->len)
				//return nullptr;
			return this->content[position];
		}

		char& front() {
			return this->at(0);
		}

		char& back() {
			return this->at(len - 1);
		}

		const char* c_str() const {
			return this->content;
		}

		char* data() const {
			return this->content;
		}

		void clear() {
			memset(this->content, 0, this->len);
			this->len = 0;
		}

		void replace(char search, char replace) {
			for (size_t i = 0; i < this->len; i++) {
				if (this->content[i] == search)
					this->content[i] = replace;
			}
		}

		bool empty() {
			return this->len == 0;
		}

		char& operator [](size_t position) {
			return this->at(position);
		}

		string& operator =(const string& string) {
			if (this->reset(string.content))
				return *this;
			this->len = string.size();
			this->bufferSize = string.size();
			delete this->content;
			this->content = new char[string.size()];
			memcpy(this->content, string.c_str(), string.size());

			return *this;
		}
		string&operator +=(const char* str) {
			const string newString(str);
			*this += newString;

			return *this;
		}
		string& operator +=(const string& str) {
			if (this->reset(str.content))
				return *this;

			size_t newLength = this->len + str.len;

			char newChar[newLength];
			memcpy(newChar, this->content, this->len);
			memcpy(newChar + this->len, str.content, str.len);
			delete this->content;
			this->content = new char[newLength];
			memcpy(this->content, newChar, newLength);
			this->len = newLength;
			this->bufferSize = newLength;

			return *this;
		}

		string operator +(const char* str) {
			string out(str);
			return  *this + out;
		}

		string operator +(const string& str) {
			string result(this->len + str.len);
			memcpy(result.content, this->content, this->len);
			memcpy(result.content + this->len, str.content, str.len);

			return result;
		}

		bool operator ==(const string& str) {
			for (size_t i = 0; i <= this->len; i++)
				if (this->content[i] != str.content[i])
					return false;
			return true;
		}
	};

}