#include "Entity.h"

Entity::Entity(PointF position, PointI size, Texture* texture, int speed) :
	GameObject( position, size, texture), speed(speed)
{
}
