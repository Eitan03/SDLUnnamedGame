#pragma once
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <assert.h>

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720
typedef SDL_Rect Rect;


struct Color {
	Color(unsigned char r, unsigned char b, unsigned char g, unsigned char a = 0xFF) : r(r), b(b), g(g), a(a) {}
	unsigned char r;
	unsigned char b;
	unsigned char g;
	unsigned char a = 0xFF;
	SDL_Color ToSDL() { return { r, g, b, a }; }
};

typedef SDL_Point PointI;
typedef struct Point : SDL_FPoint {

	//regular expressions
	inline Point operator+(const Point& other) {
		Point point = { 0, 0 };
		point.x = this->x + other.x;
		point.y = this->y + other.y;
		return point;
	}
	inline Point operator-(const Point& other) {
		Point point = { 0, 0 };
		point.x = this->x - other.x;
		point.y = this->y - other.y;
		return point;
	}
	inline Point operator*(const Point& other) {
		Point point = { 0, 0 };
		point.x = this->x * other.x;
		point.y = this->y * other.y;
		return point;
	}
	inline Point operator/(const Point& other) {
		Point point = { 0, 0 };
		point.x = this->x / other.x;
		point.y = this->y / other.y;
		return point;
	}

	// equal expressions
	inline Point& operator+=(const Point& other) {
		this->x += other.x;
		this->y += other.y;
		return *this;
	}
	inline Point& operator-=(const Point& other) {
		this->x -= other.x;
		this->y -= other.y;
		return *this;
	}
	inline Point& operator*=(const Point& other) {
		this->x *= other.x;
		this->y *= other.y;
		return *this;
	}
	inline Point& operator/=(const Point& other) {
		this->x /= other.x;
		this->y /= other.y;
		return *this;
	}

	//float expressions
	inline Point operator+(float other) {
		Point point = { 0, 0 };
		point.x = this->x + other;
		point.y = this->y + other;
		return point;
	}
	inline Point operator-(float other) {
		Point point = { 0, 0 };
		point.x = this->x - other;
		point.y = this->y - other;
		return point;
	}
	inline Point operator*(float other) {
		Point point = { 0, 0 };
		point.x = this->x * other;
		point.y = this->y * other;
		return point;
	}
	inline Point operator/(float other) {
		Point point = { 0, 0 };
		point.x = this->x / other;
		point.y = this->y / other;
		return point;
	}

	// float equal expressions
	inline Point& operator+=(float other) {
		this->x += other;
		this->y += other;
		return *this;
	}
	inline Point& operator-=(float other) {
		this->x -= other;
		this->y -= other;
		return *this;
	}
	inline Point& operator*=(float other) {
		this->x *= other;
		this->y *= other;
		return *this;
	}
	inline Point& operator/=(float other) {
		this->x /= other;
		this->y /= other;
		return *this;
	}
}; //temporary, should be moved to globals