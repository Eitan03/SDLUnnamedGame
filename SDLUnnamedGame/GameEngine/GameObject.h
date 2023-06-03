#pragma once
#include <memory>
#include <SDL.h>
#include <string>
#include <iostream>

#include "../Primitives/Texture.h"
#include "../GameEngine/Camera.h"

class GameObject : public Drawable
{
public:
	GameObject(PointF position, PointI size, std::shared_ptr<Texture> texture);
	~GameObject();
	virtual void setPosition(PointF position);
	PointF getPosition() const;
	PointI getSize() const { return this->size; };
	void changeTexture(std::shared_ptr<Texture> texture);
	void render();
	void renderABS(int x, int y) override;
	const std::shared_ptr<Texture> getTexture() { return this->texture; }; // TODO maybe weak ptr?

	//debugging
	Rect getPosABS() { return this->texture->getTextureRect(); };

protected:
	std::shared_ptr<Texture> texture;
	PointF position;
	PointI size;
};

