#pragma once
#include <SDL.h>
#include <iostream>
#include <math.h>


#include "../Utilities.h"

   //includes scale
class Camera
{
public:
	Camera();
	~Camera();
	void move(PointI pixels) { this->location += pixels; };
	void setLocation(PointI location) { this->location = location; };
	PointI getLocation(void) const { return this->location; };
	float getScale(void) const { return this->scale; };
	void setScale(float scale) { this->scale = scale; if (scale == 0) assert(false); }; //the if statement might be heavy on preformance
	void addToScale(float number) { this->setScale(scale + number); }; 
	int applyScale(int num) { return (int)round(num * scale); }; //adds the round function

private:
	PointI location;
	float scale;
};

