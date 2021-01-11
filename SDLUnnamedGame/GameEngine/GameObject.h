#pragma once
#include <memory>
#include <SDL.h>
#include <assert.h>
#include <string>
#include <iostream>

#include "../Primitives/Texture.h"
#include "../Globals.h"

class GameObject : public Drawable
{
public:
	GameObject(Point position, PointI size,std::shared_ptr<Texture> texture);
	~GameObject();
	virtual void setPosition(Point position);
	Point getPosition() const;
	PointI getSize() const { return this->size; };
	void changeTexture(std::shared_ptr<Texture> texture);
	void render();
	void renderABS(int x, int y) override;

	//debugging
	Rect getPosABS() { return this->texture.get()->getTextureRect(); };

protected:
	std::shared_ptr<Texture> texture;
	Point position;
	PointI size;

	Globals* globals;
};

