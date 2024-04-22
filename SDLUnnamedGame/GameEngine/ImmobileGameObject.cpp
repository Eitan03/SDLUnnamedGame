#include "ImmobileGameObject.h"
#include "../Blocks/Block.h"

extern Camera camera;

ImmobileGameObject::ImmobileGameObject(PointI position, PointI size, Texture* texture)
	: position(position), size(size), texture(texture)
{
}

ImmobileGameObject::~ImmobileGameObject()
{
}

void ImmobileGameObject::setPosition(PointI position)
{
	this->position.x = position.x;
	this->position.y = position.y;
}

PointI ImmobileGameObject::getPosition() const
{
	return this->position;
}

void ImmobileGameObject::changeTexture(Texture* texture)
{
	this->texture = texture;
}

void ImmobileGameObject::render()
{
	PointI location = round((PointI)this->position * Block::getSizeScaled() - static_cast<Point_impl<int>>(camera.getLocation()));
	this->texture->renderABS({ 
		location.x,
		location.y,
		camera.applyScale(this->size.x),
		camera.applyScale(this->size.y)
		});
}

void ImmobileGameObject::renderABS(int x, int y) //abs render
{
	this->position.x = x;
	this->position.y = y;
	this->texture->renderABS(this->position.x, this->position.y);
}

