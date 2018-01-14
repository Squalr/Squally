#pragma once
#include "cocos2d.h"
#include "Resources.h"

using namespace cocos2d;

class MatrixLetter : public Node
{
public:
	static MatrixLetter* create();

	void spawn();
	void despawn(float despawnTime);

private:
	MatrixLetter();
	~MatrixLetter();

	std::string generateLetter();

	Label* letter;

	static const Color3B letterColor;
	static const Color3B spawnColor;

	static const float spawnChangeRate;
	static const float spawnTime;
	static const float fadeOutPercentage;
	static const float letterChangePercentage;
};
