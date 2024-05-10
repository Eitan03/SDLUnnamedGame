#pragma once
#include <memory>
#include <string>
#include <iostream>

#include <MyGraphicsLibrary/Texture.h>
#include "../GameEngine/Camera.h"

class MobileGameObject : public MGL::Drawable
{
public:
	MobileGameObject(MGL::PointF position, MGL::PointI size, std::shared_ptr<MGL::Texture> texture);
	~MobileGameObject();
	virtual void setPosition(MGL::PointF position);
	MGL::PointF getPosition() const;
	MGL::PointI getSize() const { return this->size; };
	void changeTexture(std::shared_ptr<MGL::Texture> texture);
	void render(MGL::PointF position, MGL::PointI size);
	virtual void render();
	void renderABS(int x, int y) override;
	const std::shared_ptr<MGL::Texture> getTexture() { return this->texture; }; // TODO maybe weak ptr?

	//debugging
	MGL::Rect getPosABS() { return this->texture->getTextureRect(); };

protected:
	std::shared_ptr<MGL::Texture> texture;
	MGL::PointF position;
	MGL::PointI size;
};

