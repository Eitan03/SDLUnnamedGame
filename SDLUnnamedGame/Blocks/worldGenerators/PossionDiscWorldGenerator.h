#pragma once
#include "WorldGenerator.h"
#include <vector>
#define _USE_MATH_DEFINES // for M_PI
#include <math.h>
#include <cstdlib> //for random

class PossionDiscWorldGenerator :
    public WorldGenerator
{
public:
    PossionDiscWorldGenerator();
    int getBlock(MGL::PointI pos) override;

private:
    std::vector<MGL::PointI> points;
    const unsigned int sampleSize = 128;
    const unsigned int radius = 32;
};

std::vector<MGL::PointI> possionDisk(float raduis, MGL::PointI sampleRegionSize, int maxRejection = 30);

bool isValid(MGL::PointI candidatePoint, float radius, MGL::PointI sampleRegionSize, float cellSize, std::vector<MGL::PointI> points, std::vector< std::vector<int> > grid);

float randValue();

int randrange(int minNumber, int maxNumber);
