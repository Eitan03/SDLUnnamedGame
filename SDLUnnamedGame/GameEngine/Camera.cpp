#include "Camera.h"
#include "../Blocks/Block.h"

Camera::Camera()
	: location( { 0, 0 } ), scale(1.0f)
{
	Block::cam = this;
}



void Camera::setLocation(PointI location)
{
	this->location = location; this->update();
}

void Camera::setScale(float scale)
{
	this->scale = scale; if (scale == 0) assert(false); this->update();
	std::cout << this->scale << std::endl;
}

void Camera::update()
{
	subject::update();
	Block::update();
}
