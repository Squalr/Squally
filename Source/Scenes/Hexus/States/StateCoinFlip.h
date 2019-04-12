#pragma once

#include "Scenes/Hexus/States/StateBase.h"

namespace cocos2d
{
	class Animation;
	class Sprite;
}

class SmartAnimationSequenceNode;

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
	typedef StateBase super;
	StateCoinFlip();
	~StateCoinFlip();

	void onEnter() override;
	void initializePositions() override;

	SmartAnimationSequenceNode* coinAnimation;
};
