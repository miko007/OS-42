//
// Created by miko on 30.10.16.
//

#pragma once

namespace drivers {

	class Driver {
	protected:
		Driver() {}
	public:
		virtual void activate() {}
		virtual void deactivate() {}
		virtual int reset() {
			return 0;
		}
	};

}