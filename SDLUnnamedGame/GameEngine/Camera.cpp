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
	this->scale = scale; 
	if (-0.01 < scale && scale < 0.01) 
		throw GameEngineException("scale cant be 0");
	this->update();

	std::cout << "scale: " << this->scale << std::endl;
}

void Camera::update()
{
	subject::update();
	Block::update();
}
