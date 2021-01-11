#pragma once
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <assert.h>

#include "Utilities.h"
#include "./GameEngine/Camera.h"

class Globals
{
public:
    static Globals* getInstance()
    {
        if (instance == nullptr) {
            instance = new Globals();
        }
        return instance;
    }

    static Globals* instance;
    // Note: Scott Meyers mentions in his Effective Modern
    //       C++ book, that deleted functions should generally
    //       be public as it results in better error messages
    //       due to the compilers behavior to check accessibility
    //       before deleted status

    const int BlockSize;
    int BlockSizeScaled; //insted of writing appleScale(BlockSize) multiple times

    Camera camera;

    struct Colors {
        const Color White;
        const Color Black;
    };

    Colors colors;

    enum BlockTypes {
        Grass,
        Sand
    };

    //Point gridToScreen(Point gridPos);

private:
    Globals();
    ~Globals() { delete instance; };
};