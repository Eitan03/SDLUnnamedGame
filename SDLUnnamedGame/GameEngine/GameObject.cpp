#include "GameObject.h"
#include "../Blocks/Block.h"

extern Camera camera;

GameObject::GameObject(PointF position, PointI size, Texture* texture)
	: position(position), size(size), texture(texture)
{
}

GameObject::~GameObject()
{
}

void GameObject::setPosition(PointF position)
{
	this->position.x = position.x;
	this->position.y = position.y;
}

PointF GameObject::getPosition() const
{
	return this->position;
}

void GameObject::changeTexture(Texture* texture)
{
	this->texture = texture;
}

void GameObject::render()
{
	PointI location = round((PointI)this->position * Block::getSizeScaled() - static_cast<Point_impl<int>>(camera.getLocation()));
	this->texture->renderABS({ 
		location.x,
		location.y,
		camera.applyScale(this->size.x),
		camera.applyScale(this->size.y)
		});
}

void GameObject::renderABS(int x, int y) //abs render
{
	this->position.x = x;
	this->position.y = y;
	this->texture->renderABS(this->position.x, this->position.y);
}

