#pragma once

#define STRING_DEFAULT_LENGTH 15

#include <iostream.hpp>

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
		size_t length;
		uint32_t bufferSize;
		char* content;
	public:
		string(size_t length = STRING_DEFAULT_LENGTH) :
				content(new char[length]), length(0), bufferSize(length) {
			memset(this->content, 0, length);
		}
		string(const char* string) {
			size_t length    = strlen(string) + 1;
			this->content    = new char[length];
			this->length     = length - 1;
			this->bufferSize = length;
			memcpy(this->content, string, length);
		}
		string(const string& string) :
				content(new char[string.length]), length(string.length),
				bufferSize(string.bufferSize){
			memcpy(this->content, string.c_str() - 1, string.length);
		}
		~string() {
			if (this->content)
				delete[] this->content;
		}
		size_t size() const {
			return this->length;
		}

		const char* c_str() const {
			return this->content;
		}

		string& operator =(const string& string) {
			this->length = string.size();
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
			size_t newLength = this->length + str.length;

			char newChar[newLength];
			memcpy(newChar, this->content, this->length);
			memcpy(newChar + this->length, str.content, str.length);
			cout << " >>>> '" << newChar << "', " << std::decimal(newLength) << endl;
			delete this->content;
			this->content = new char[newLength];
			memcpy(this->content, newChar, newLength);
			this->length = newLength;
			this->bufferSize = newLength;

			return *this;
		}

		string operator +(const char* str) {
			string out(str);
			return  *this + out;
		}

		string operator +(const string& str) {
			string result(this->length + str.length);
			memcpy(result.content, this->content, this->length);
			memcpy(result.content + this->length, str.content, str.length);

			return result;
		}

		bool operator ==(const string& str) {
			for (size_t i = 0; i <= this->length; i++)
				if (this->content[i] != str.content[i])
					return false;
			return true;
		}
	};

}