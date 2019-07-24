#pragma once
#include "cocos/2d/CCSprite.h"
#include "cocos/base/ccTypes.h"

class MatrixLetter : public cocos2d::Sprite
{
public:
	static MatrixLetter* create();

	void spawnImmediate();
	void spawn();
	void despawn();

	static const int LetterSize;

private:
	typedef cocos2d::Sprite super;
	MatrixLetter();
	~MatrixLetter();

	void pause(void) override;
	void randomizeLetter();

	static const cocos2d::Color3B LetterColor;
	static const cocos2d::Color3B SpawnColor;
	static const cocos2d::Color4B GlowColor;

	static const float SpawnChangeRate;
	static const float SpawnTime;
	static const float FadeOutPercentage;
	static const float LetterChangePercentage;
};
