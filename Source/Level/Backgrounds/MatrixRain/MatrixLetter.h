#pragma once
#include "cocos2d.h"
#include "Resources.h"

using namespace cocos2d;

class MatrixLetter : public Sprite
{
public:
	static MatrixLetter* create();

	void spawn();
	void despawn();

	static const int letterSize;

private:
	MatrixLetter();
	~MatrixLetter();

	virtual void pause(void) override;
	void randomizeLetter();

	static const Color3B letterColor;
	static const Color3B spawnColor;
	static const Color4B glowColor;

	static const float spawnChangeRate;
	static const float spawnTime;
	static const float fadeOutPercentage;
	static const float letterChangePercentage;
};
