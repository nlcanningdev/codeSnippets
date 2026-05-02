#include "areaMap.h"
#include <cstdint>

AreaMap::AreaMap(size_t areaMapTileNumX, size_t areaMapTileNumY, size_t maxNumActorOccupyingTile) : areaMapTileNumX(areaMapTileNumX), areaMapTileNumY(areaMapTileNumY), maxNumActorOccupyingTile(maxNumActorOccupyingTile) {
	this->actorOccupyingTileIndex = new size_t**[this->areaMapTileNumX];
	this->currentActorOccupyingTileNum = new size_t*[this->areaMapTileNumX];
	for (size_t a = 0; a < this->areaMapTileNumX; ++a) {
		this->actorOccupyingTileIndex[a] = new size_t*[this->areaMapTileNumY];
		this->currentActorOccupyingTileNum = new size_t[this->areaMapTileNumY];
		for (size_t b = 0; b < this->areaMapTileNumY; ++b) {
			this->actorOccupyingTileIndex[a][b] = new size_t[this->maxNumActorOccupyingTile];
			this->currentActorOccupyingTileNum[a][b] = 0;
		}
	}
}

AreaMap::~AreaMap() {
	for (size_t a = 0; a < this->areaMapTileNumX; ++a) {
		for (size_t b = 0; b < this->areaMapTileNumY; ++b) {
			delete[] this->actorOccupyingTileIndex[a][b];
		}
		delete[] this->actorOccupyingTileIndex[a];
		delete[] this->currentActorOccupyingTileNum[a];
	}
	delete[] this->actorOccupyingTileIndex;
	delete[] this->currentActorOccupyingTileNum;
}

size_t AreaMap::getPossibleCollisionActors(size_t* collisionData, size_t maxCollisionDataNum, size_t currentCollisionDataNum, size_t currentActorIndex) {
	return;
}