#include "ImmobileGameObject.h"
#include "../Blocks/Block.h"

extern Camera camera;

ImmobileGameObject::ImmobileGameObject(MGL::PointF position, MGL::PointI size, std::shared_ptr<MGL::Texture> texture)
	: position(position), size(size), texture(texture)
{
}

ImmobileGameObject::~ImmobileGameObject()
{
}

void ImmobileGameObject::setPosition(MGL::PointF position)
{
	this->position.x = position.x;
	this->position.y = position.y;
}

MGL::PointF ImmobileGameObject::getPosition() const
{
	return this->position;
}

void ImmobileGameObject::changeTexture(std::shared_ptr<MGL::Texture> texture)
{
	this->texture = texture;
}

void ImmobileGameObject::render(MGL::PointF position, MGL::PointI size)
{
	MGL::PointI location = (MGL::PointI)round(position * (float)Block::getSizeScaled() - ((MGL::PointF)camera.getLocation()));
	this->texture->renderABS({
		location.x,
		location.y,
		camera.applyScale(size.x),
		camera.applyScale(size.y)
		});
}

void ImmobileGameObject::render()
{
	this->render(this->position, this->size);
}

void ImmobileGameObject::renderABS(int x, int y) //abs render
{
	this->position.x = x;
	this->position.y = y;
	this->texture->renderABS(this->position.x, this->position.y);
}

