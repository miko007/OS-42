//
// Created by miko on 22.10.16.
//

#pragma once

#include <types.hpp>

namespace std {

	class iostream {
	public:
		iostream();
		iostream& operator<<(const char* str);
	};

	extern iostream cout;
	extern char* endl;

}