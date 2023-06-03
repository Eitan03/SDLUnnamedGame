#pragma once
#include <map>
#include <vector>

#include "Texture.h"


// a texture that can be used as a draw target to combine multiple textures
class TargetTexture :
    public Texture
{
public:
    TargetTexture(Renderer& renderer, Rect textureRect = { -1, -1, -1, -1});

    void DrawToTexture(std::map<std::shared_ptr<Texture>, std::vector<PointI>> textures);
};

