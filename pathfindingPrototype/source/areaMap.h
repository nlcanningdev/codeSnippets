#pragma once

class AreaMap {
public:
	AreaMap(size_t areaMapTileNumX, size_t areaMapTileNumY
		, size_t maxNumActorOccupyingTile);
	~AreaMap();
	size_t getPossibleCollisionActors(size_t* collisionData, size_t maxCollisionDataNum, size_t currentCollisionDataNum, size_t currentActorIndex);
private:
	size_t*** actorOccupyingTileIndex;
	size_t areaMapTileNumX;
	size_t areaMapTileNumY;
	size_t maxNumActorOccupyingTile;
	size_t* currentActorOccupyingTileNum;
};