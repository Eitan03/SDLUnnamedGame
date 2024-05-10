#include "MobileGameObject.h"
#include "../Blocks/Block.h"

extern Camera camera;

MobileGameObject::MobileGameObject(MGL::PointF position, MGL::PointI size, std::shared_ptr<MGL::Texture> texture)
	: position(position), size(size), texture(texture)
{
}

MobileGameObject::~MobileGameObject()
{
}

void MobileGameObject::setPosition(MGL::PointF position)
{
	this->position.x = position.x;
	this->position.y = position.y;
}

MGL::PointF MobileGameObject::getPosition() const
{
	return this->position;
}

void MobileGameObject::changeTexture(std::shared_ptr<MGL::Texture> texture)
{
	this->texture = texture;
}

void MobileGameObject::render(MGL::PointF position, MGL::PointI size)
{
	MGL::PointI location = (MGL::PointI)round(position * (float)Block::getSizeScaled() - ((MGL::PointF)camera.getLocation()));
	this->texture->renderABS({
		location.x,
		location.y,
		camera.applyScale(size.x),
		camera.applyScale(size.y)
		});
}

void MobileGameObject::render()
{
	this->render(this->position, this->size);
}

void MobileGameObject::renderABS(int x, int y) //abs render
{
	this->position.x = x;
	this->position.y = y;
	this->texture->renderABS(this->position.x, this->position.y);
}

