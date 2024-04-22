#include "Entity.h"

Entity::Entity(PointF position, PointI size, Texture* texture, int speed) :
	MobileGameObject( position, size, texture), speed(speed)
{
}
