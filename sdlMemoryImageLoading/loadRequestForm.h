#pragma once

#include <string>

struct LoadRequestForm {
	LoadRequestForm() : canBeOverwritten(true), surfaceLoadRequired(false), textureLoadRequired(false) {}
	bool surfaceLoadRequired;
	bool textureLoadRequired;
	bool canBeOverwritten;
	std::string fileName;
	int resourceSize;
	int resourceStart;
	int surfaceIndex;
	int textureIndex;
};