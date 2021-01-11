#include "GameObject.h"



GameObject::GameObject(PointF position, PointI size, std::shared_ptr<Texture> texture)
	: position(position), size(size), texture(texture), globals(Globals::getInstance())
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

void GameObject::changeTexture(std::shared_ptr<Texture> texture)
{
	this->texture = texture;
}

void GameObject::render()
{
	this->texture->renderABS({ 
		(int) round(this->position.x * globals->camera.applyScale(globals->BlockSize)  - (globals->camera.getLocation().x) ),
		(int) round(this->position.y * globals->camera.applyScale(globals->BlockSize)  - globals->camera.getLocation().y) ,
		globals->camera.applyScale(this->size.x),
		globals->camera.applyScale(this->size.y)
		});
}

void GameObject::renderABS(int x, int y) //abs render
{
	this->position.x = x;
	this->position.y = y;
	this->texture->renderABS(this->position.x, this->position.y);
}

