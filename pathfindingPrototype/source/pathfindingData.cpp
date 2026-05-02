#include "pathfindingData.h"
#include <cstdint>

PathfindingData::PathfindingData(size_t nodeMaxNum) {
	this->nodeMaxNum = nodeMaxNum;
	this->node = new float*[this->nodeMaxNum];
	for (size_t a = 0; a < this->nodeMaxNum; ++a) {
		this->node[a] = new float[2];
	}
	this->nodeCurrentNum = 0;
	this->currentNode = 0;
}

PathfindingData::~PathfindingData() {
	for (size_t a = 0; a < this->nodeMaxNum; ++a) {
		delete[] this->node[a];
	}
	delete[] this->node;
}

float PathfindingData::getCurrentNodeX() {
	return this->node[this->currentNode][0];
}

float PathfindingData::getCurrentNodeY() {
	return this->node[this->currentNode][1];
}

bool PathfindingData::getPathComplete() {
	if (this->currentNode == this->nodeCurrentNum)
		return true;
	return false;
}