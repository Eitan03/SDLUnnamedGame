#pragma once
#include <SDL.h>
#include <iostream>
#include <math.h>


#include "../Utilities.h"
#include "../Pattrens/subject.h"

   //includes scale

/*
only supports one camera object because of block
*/
class Camera: public subject
{
public:
	~Camera() {};
	Camera();
	void setLocation(PointI location);
	void move(PointI pixels) { this->setLocation(location + pixels); };
	PointI getLocation(void) const { return this->location; };
	float getScale(void) const { return this->scale; };
	void setScale(float scale); //the if statement might be heavy on preformance
	void addToScale(float number) { this->setScale(scale + number); }; 
	int applyScale(int num) { return (int)round(num * scale); }; //adds the round function

	void temp() {};
protected:
	void update() override;
private:
	PointI location;
	float scale;
};

