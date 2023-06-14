#include "GameObject.h"
#include "../Blocks/Block.h"

extern Camera camera;

GameObject::GameObject(MGL::PointF position, MGL::PointI size, std::shared_ptr<MGL::Texture> texture)
	: position(position), size(size), texture(texture)
{
}

GameObject::~GameObject()
{
}

void GameObject::setPosition(MGL::PointF position)
{
	this->position.x = position.x;
	this->position.y = position.y;
}

MGL::PointF GameObject::getPosition() const
{
	return this->position;
}

void GameObject::changeTexture(std::shared_ptr<MGL::Texture> texture)
{
	this->texture = texture;
}

void GameObject::render()
{
	MGL::PointI location = round((MGL::PointI)this->position * Block::getSizeScaled() - static_cast<Point_impl<int>>(camera.getLocation()));
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

