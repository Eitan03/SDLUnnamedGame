#include "Camera.h"
#include "../Blocks/Block.h"

Camera::Camera()
	: location( { 0, 0 } ), scale(1.0f)
{
}



void Camera::setLocation(MGL::PointI location)
{
	this->location = location; this->notifyObservers(this);
}

void Camera::setScale(float scale)
{
	this->scale = scale; 
	if (-0.01 < scale && scale < 0.01) 
		throw GameEngineException("scale cant be 0");
	this->notifyObservers(this);

	std::cout << "scale: " << this->scale << std::endl;
}

void Camera::notifyObservers(Camera* cam)
{
	for (auto obs : observers) {
		obs(this);
	}
}
