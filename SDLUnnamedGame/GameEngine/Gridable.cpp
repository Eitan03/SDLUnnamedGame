#include "Gridable.h"
#include "../Blocks/Block.h"

extern Camera camera;

Gridable::Gridable(MGL::PointI position, MGL::PointI size, std::shared_ptr<MGL::Texture> texture)
	: position(position), size(size), texture(texture)
{
}

Gridable::~Gridable()
{
}

void Gridable::setPosition(MGL::PointI position)
{
	this->position.x = position.x;
	this->position.y = position.y;
}

MGL::PointI Gridable::getPosition() const
{
	return this->position;
}

void Gridable::changeTexture(std::shared_ptr<MGL::Texture> texture)
{
	this->texture = texture;
}

void Gridable::render(MGL::PointI position, MGL::PointI size)
{
	MGL::PointI location = round(position * Block::getSizeScaled() - static_cast<MGL::PointI>(camera.getLocation()));
	this->texture->renderABS({ 
		location.x,
		location.y,
		camera.applyScale(size.x),
		camera.applyScale(size.y)
		});
}

void Gridable::render()
{
	this->render(this->position, this->size);
}

void Gridable::renderABS(int x, int y)
{
	this->position.x = x;
	this->position.y = y;
	this->texture->renderABS(this->position.x, this->position.y);
}

