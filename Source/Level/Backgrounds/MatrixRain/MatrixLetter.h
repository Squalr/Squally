#pragma once
#include "cocos2d.h"
#include "Resources.h"

using namespace cocos2d;

class MatrixLetter : public Label
{
public:
	static MatrixLetter* create();

	void spawn();
	void despawn(float despawnTime);

private:
	MatrixLetter();
	~MatrixLetter();

	std::string generateLetter();

	static const Color3B letterColor;
	static const Color3B spawnColor;
	static const Color4B glowColor;

	static const float spawnChangeRate;
	static const float spawnTime;
	static const float fadeOutPercentage;
	static const float letterChangePercentage;
};
