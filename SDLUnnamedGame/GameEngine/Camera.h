#pragma once
#include <SDL.h>
#include <iostream>
#include <math.h>


#include "../Utilities.h"
#include "../Pattrens/subject.h"

   //includes scale
class Camera: subject
{
public:
	Camera();
	~Camera() override {};
	void setLocation(PointI location);
	void move(PointI pixels) { this->setLocation(location+ pixels); };
	PointI getLocation(void) const { return this->location; };
	float getScale(void) const { return this->scale; };
	void setScale(float scale); //the if statement might be heavy on preformance
	void addToScale(float number) { this->setScale(scale + number); }; 
	int applyScale(int num) { return (int)round(num * scale); }; //adds the round function

	void temp() {};

private:
	PointI location;
	float scale;
};

