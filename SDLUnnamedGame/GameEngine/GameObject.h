#pragma once
#include <memory>
#include <SDL.h>
#include <assert.h>
#include <string>
#include <iostream>

#include "../Primitives/Texture.h"
#include "../GameEngine/Camera.h"

class GameObject : public Drawable
{
public:
	GameObject(PointF position, PointI size, Texture* texture);
	~GameObject();
	virtual void setPosition(PointF position);
	PointF getPosition() const;
	PointI getSize() const { return this->size; };
	void changeTexture(Texture* texture);
	void render();
	void renderABS(int x, int y) override;

	//debugging
	Rect getPosABS() { return this->texture->getTextureRect(); };

protected:
	Texture* texture;
	PointF position;
	PointI size;
};

