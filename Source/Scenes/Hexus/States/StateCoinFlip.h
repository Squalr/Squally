#pragma once

#include "Scenes/Hexus/States/StateBase.h"

namespace cocos2d
{
	class Animation;
	class Sprite;
}

class StateCoinFlip : public StateBase
{
public:
	static StateCoinFlip* create();

protected:
	void onBeforeStateEnter(GameState* gameState) override;
	void onStateEnter(GameState* gameState) override;
	void onStateReload(GameState* gameState) override;
	void onStateExit(GameState* gameState) override;

private:
	StateCoinFlip();
	~StateCoinFlip();

	void onEnter() override;
	void initializePositions() override;

	cocos2d::Sprite* coin;
	cocos2d::Animation* skeletonInAnimation;
	cocos2d::Animation* skeletonOutAnimation;
	cocos2d::Animation* lionInAnimation;
	cocos2d::Animation* lionOutAnimation;
	cocos2d::Animation* neutralAnimation;
};
