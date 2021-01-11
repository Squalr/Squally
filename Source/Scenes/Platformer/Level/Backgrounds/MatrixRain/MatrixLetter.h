#pragma once

#include "cocos/2d/CCNode.h"

namespace cocos2d
{
	class Sprite;
}

template <class T> class LazyNode;

class MatrixLetter : public cocos2d::Node
{
public:
	static MatrixLetter* create();

	void build();
	void spawnImmediate();
	void spawn();
	void despawn();

	static const int LetterSize;

protected:
	MatrixLetter();
	virtual ~MatrixLetter();

private:
	typedef cocos2d::Node super;

	void pause(void) override;
	void randomizeLetter(cocos2d::Sprite* target);
	cocos2d::Sprite* buildSprite();

	LazyNode<cocos2d::Sprite>* sprite;

	static const cocos2d::Color3B LetterColor;
	static const cocos2d::Color3B SpawnColor;
	static const cocos2d::Color4B GlowColor;

	static const float SpawnChangeRate;
	static const float SpawnTime;
	static const float FadeOutPercentage;
	static const float LetterChangePercentage;
};
