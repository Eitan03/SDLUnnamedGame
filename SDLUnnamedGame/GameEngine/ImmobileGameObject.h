#pragma once
#include <memory>
#include <SDL.h>
#include <string>
#include <iostream>

#include "../Primitives/Texture.h"
#include "../GameEngine/Camera.h"

// meaning its position is PointI since it can NOT move
// i.e block
class ImmobileGameObject : public Drawable
{
public:
	ImmobileGameObject(PointI position, PointI size, Texture* texture);
	~ImmobileGameObject();
	virtual void setPosition(PointI position);
	PointI getPosition() const;
	PointI getSize() const { return this->size; };
	void changeTexture(Texture* texture);
	void render();
	void renderABS(int x, int y) override;
	const Texture* getTexture() { return this->texture; };

	// for debugging
	Rect getPosABS() { return this->texture->getTextureRect(); };

protected:
	Texture* texture;
	PointI position;
	PointI size;
};

