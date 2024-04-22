#include "MobileGameObject.h"
#include "../Blocks/Block.h"

extern Camera camera;

MobileGameObject::MobileGameObject(PointF position, PointI size, Texture* texture)
	: position(position), size(size), texture(texture)
{
}

MobileGameObject::~MobileGameObject()
{
}

void MobileGameObject::setPosition(PointF position)
{
	this->position.x = position.x;
	this->position.y = position.y;
}

PointF MobileGameObject::getPosition() const
{
	return this->position;
}

void MobileGameObject::changeTexture(Texture* texture)
{
	this->texture = texture;
}

void MobileGameObject::render()
{
	PointI location = round((PointI)this->position * Block::getSizeScaled() - static_cast<Point_impl<int>>(camera.getLocation()));
	this->texture->renderABS({ 
		location.x,
		location.y,
		camera.applyScale(this->size.x),
		camera.applyScale(this->size.y)
		});
}

void MobileGameObject::renderABS(int x, int y) //abs render
{
	this->position.x = x;
	this->position.y = y;
	this->texture->renderABS(this->position.x, this->position.y);
}

