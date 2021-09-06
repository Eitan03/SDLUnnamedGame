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
    int getBlock(PointI pos) override;

private:
    std::vector<PointI> points;
    const unsigned int sampleSize = 6;
};

std::vector<PointI> possionDisk(float raduis, PointI sampleRegionSize, int maxRejection = 30);

bool isValid(PointI candidatePoint, float radius, PointI sampleRegionSize, float cellSize, std::vector<PointI> points, std::vector< std::vector<int> > grid);

float randValue();

int randrange(int minNumber, int maxNumber);
