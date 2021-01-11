#pragma once

#include "../GameEngine/GameObject.h"



class Block: public GameObject
{
public:
	Block(PointI position, std::shared_ptr<Texture> texture);
	~Block();
	//for debugging;
	void setSize(PointI size) { this->size = size; }

protected:
	
};

