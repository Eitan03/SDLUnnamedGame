#pragma once
#include "Texture.h"


// a texture that can be used as a draw target to combine multiple textures
class TargetTexture :
    public Texture
{
public:
    TargetTexture(Renderer& renderer, Rect textureRect = { -1, -1, -1, -1});

    void DrawToTexture(Texture* textures, PointI texturePositions, size_t texturesSize);
};

