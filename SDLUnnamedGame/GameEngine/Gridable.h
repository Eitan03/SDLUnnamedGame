#pragma once
#include <memory>
#include <string>
#include <iostream>

#include <MyGraphicsLibrary/Texture.h>
#include "../GameEngine/Camera.h"

// can only be placed in the game grid
class Gridable : public MGL::Drawable
{
public:
	Gridable(MGL::PointI position, MGL::PointI size, std::shared_ptr<MGL::Texture> texture);
	~Gridable();
	virtual void setPosition(MGL::PointI position);
	MGL::PointI getPosition() const;
	MGL::PointI getSize() const { return this->size; };
	void changeTexture(std::shared_ptr<MGL::Texture> texture);
	void render(MGL::PointI position, MGL::PointI size);
	virtual void render();
	void renderABS(int x, int y) override;
	const std::shared_ptr<MGL::Texture> getTexture() { return this->texture; }; // TODO maybe weak ptr?

	//debugging
	MGL::Rect getPosABS() { return this->texture->getTextureRect(); };

protected:
	std::shared_ptr<MGL::Texture> texture;
	MGL::PointI position;
	MGL::PointI size;
};

