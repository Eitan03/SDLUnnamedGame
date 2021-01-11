#include "Globals.h"

Globals* Globals::instance = nullptr;

Globals::Globals():
	BlockSize(SCREEN_WIDTH / 16), camera(Camera()), BlockSizeScaled(BlockSize),
	colors(
		{
			{255, 255, 255}, //White
			{0 ,0 ,0} //Black
		}
	)
{

};


/*
Point GLOBALS::gridToScreen(Point gridPos) { //does not include GLOBALS::camera pos atm
	return { ( gridPos.x * (int)(GLOBALS::BlockSize / GLOBALS::camera.getScale()) ) , ( gridPos.y * (int)(GLOBALS::BlockSize / GLOBALS::camera.getScale()) ) };
};
*/