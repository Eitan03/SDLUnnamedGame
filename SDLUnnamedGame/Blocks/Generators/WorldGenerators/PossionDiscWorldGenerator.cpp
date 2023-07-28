#include "PossionDiscWorldGenerator.h"


PossionDiscWorldGenerator::PossionDiscWorldGenerator() {
	points = possionDisk(radius, MGL::PointI(sampleSize, sampleSize));
}

int PossionDiscWorldGenerator::getBlock(MGL::PointI position) {
	
	MGL::PointI currPosition = position; // abs(position) % (int)sampleSize;
	if (std::find(points.begin(), points.end(), currPosition) != points.end()) {
		return 1;
	}
	else {
		return 0;
	}

}


// @TODO srand to seed the random generator
std::vector<MGL::PointI> possionDisk(float raduis, MGL::PointI sampleRegionSize, int maxRejection
) {
	float cellSize = raduis / sqrt(2);

	// TODO dynamic array instead
	std::vector< std::vector<int> > grid(
		ceil(sampleRegionSize.x / cellSize), std::vector<int>( ceil(sampleRegionSize.y / cellSize), -1 )
		);

	std::vector<MGL::PointI> points = std::vector<MGL::PointI>();
	std::vector<MGL::PointI> spawnPoints = std::vector<MGL::PointI>();
	
	spawnPoints.push_back(MGL::PointI(sampleRegionSize / 2));

	while (spawnPoints.size() > 0) {
		int spawnIndex = randrange(0, spawnPoints.size() - 1 );
		MGL::PointI spawnCentre = spawnPoints[spawnIndex];
		bool candidateAccepted = false;

		for (int i = 0; i < maxRejection; i++) {
			float angle = randValue() * M_PI * 2; //random angle in radians
			MGL::PointF dir = { sin(angle), cos(angle) }; // random direction
			MGL::PointI candidate = (MGL::PointI)((MGL::PointF)spawnCentre + dir * (float)randrange(raduis, raduis * 2));

			if (isValid(candidate, raduis, sampleRegionSize, cellSize, points, grid)) {
				points.push_back(candidate);
				spawnPoints.push_back(candidate);
				if (grid[(int)(candidate.x / cellSize)][(int)(candidate.y / cellSize)] != -1) {
					std::cout << "wierd overriding" << std::endl;
				}
				grid[(int)(candidate.x / cellSize)][(int)(candidate.y / cellSize)] = points.size() - 1;
				candidateAccepted = true;
				break;
			}
		}
		if (!candidateAccepted) {
			spawnPoints.erase(spawnPoints.begin() + spawnIndex);
		}
	}
	return points;
}

bool isValid(MGL::PointI candidatePoint, float radius, MGL::PointI sampleRegionSize, float cellSize, std::vector<MGL::PointI> points, std::vector< std::vector<int> > grid) {
	if ((candidatePoint.x < sampleRegionSize.x) && (candidatePoint.x >= 0) && (candidatePoint.y < sampleRegionSize.y) && (candidatePoint.y >= 0)) {
		MGL::PointI cell = (MGL::PointI)( (MGL::PointF)candidatePoint / cellSize );

		int searchStartX = std::max(0, cell.x - 2);
		int searchEndX = std::min(cell.x + 2, int(grid.size()) );

		int searchStartY = std::max(0, cell.y - 2);
		int searchEndY = std::min(cell.y + 2, int(grid[0].size()));

		for (int x = searchStartX; x < searchEndX; x++) {
			for (int y = searchStartY; y < searchEndY; y++) {
				int pointIndex = grid[x][y];
				if (pointIndex != -1) {
					float sqrDistance = sqrMagnitude(candidatePoint - points[pointIndex]);
					if (sqrDistance < radius * radius) {
						return false;
					}
				}
			}
		}
		return true;
	}
	return false;

}

float randValue() {
	//random value between 0 and 1
	return (double)std::rand() / RAND_MAX;
}

int randrange(int minNumber, int maxNumber) {
	float randNumber = randValue();
	randNumber = minNumber + (int)round(randNumber * (maxNumber - minNumber));
	return randNumber;
}