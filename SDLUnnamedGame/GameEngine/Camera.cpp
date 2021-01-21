#include "Camera.h"
#include "../Blocks/ChunkManager.h"

Camera::Camera()
	: location( { 0, 0 } ), scale(1.0f), chunkManager(nullptr)
{
}

Camera::~Camera()
{
}

void Camera::setLocation(PointI location)
{
	this->location = location; chunkManager->update(location, scale);
}

void Camera::setScale(float scale)
{
	this->scale = scale; if (scale == 0) assert(false); chunkManager->update(location, scale);
}
