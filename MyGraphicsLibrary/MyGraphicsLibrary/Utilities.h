#pragma once
#include "Point.h"

namespace MGL {

	struct MyGraphicsLibraryException : public std::exception {
		MyGraphicsLibraryException(std::string msg) : _msg(msg) {}
		const char* what() const throw () {
			return _msg.c_str();
		}

	private:
		std::string _msg;
	};

	struct Color {
		uint8_t r = 0;
		uint8_t g = 0;
		uint8_t b = 0;
		uint8_t a = 0xFF;
	};

	struct Rect {
		int x = -1;
		int y = -1;
		int w = -1;
		int h = -1;

		void setPosition(PointI pos) {
			this->x = pos.x;
			this->y = pos.y;
		};

		PointI getPosition() {
			return PointI(this->x, this->y);
		};

		void setSize(PointI size) {
			this->w = size.x;
			this->h = size.y;
		};

		PointI getSize() {
			return PointI(this->w, this->h);
		};
	};
}
