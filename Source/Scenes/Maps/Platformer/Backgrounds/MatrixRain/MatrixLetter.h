#pragma once
#include "cocos/2d/CCSprite.h"
#include "cocos/base/ccTypes.h"

#include "Engine/SmartNode.h"

class MatrixLetter : public cocos2d::Sprite
{
public:
	static MatrixLetter* create();

	void spawn();
	void despawn();

	static const int letterSize;

private:
	typedef cocos2d::Sprite super;
	MatrixLetter();
	~MatrixLetter();

	virtual void pause(void) override;
	void randomizeLetter();

	static const cocos2d::Color3B letterColor;
	static const cocos2d::Color3B spawnColor;
	static const cocos2d::Color4B glowColor;

	static const float spawnChangeRate;
	static const float spawnTime;
	static const float fadeOutPercentage;
	static const float letterChangePercentage;
};
