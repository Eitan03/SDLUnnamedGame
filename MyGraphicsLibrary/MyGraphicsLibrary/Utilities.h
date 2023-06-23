#pragma once
#include <SDL.h>
#include "Point.h"

namespace MGL {

	struct MyGraphicsLibraryException : public std::exception {
		MyGraphicsLibraryException(std::string msg): _msg(msg) {  }
		const char* what() const throw () {
			return _msg.c_str();
		}

	private:
		std::string _msg;
	};

	struct Color : public SDL_Color {
		Color(Uint8 r, Uint8 g, Uint8 b, Uint8 a = 0xFF) : SDL_Color{ r,b,g,a } {}
	};

	struct Rect : public SDL_Rect {
		Rect(int x, int y, int w, int h) : SDL_Rect{x, y, w, h} {}
		Rect() : SDL_Rect{} {}

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
