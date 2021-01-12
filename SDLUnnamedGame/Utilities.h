#pragma once
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <assert.h>

#include "Point.h"

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

struct Color {
	Color(unsigned char r, unsigned char b, unsigned char g, unsigned char a = 0xFF) : r(r), b(b), g(g), a(a) {}
	unsigned char r;
	unsigned char b;
	unsigned char g;
	unsigned char a = 0xFF;
	SDL_Color ToSDL() { return { r, g, b, a }; }
};



struct Rect : public SDL_Rect {
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