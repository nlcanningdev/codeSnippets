#pragma once

#include <cstdint>

class PathfindingData {
public:
	PathfindingData(size_t nodeMaxNum);
	~PathfindingData();
	float getCurrentNodeX();
	float getCurrentNodeY();
	bool getPathComplete();
private:
	float** node; //not sure about this
	size_t nodeMaxNum;
	size_t nodeCurrentNum;
	size_t currentNode;
};

/*
not sure about the best way to do this yet
after reaching the final node, +1 currentNode so it's equal to nodeCurrentNum
*/