#pragma once

#include "Scenes/Hexus/States/StateBase.h"

class SmartAnimationSequenceNode;

class StateCoinFlip : public StateBase
{
public:
	static StateCoinFlip* create();

protected:
	StateCoinFlip();
	virtual ~StateCoinFlip();

	void onEnter() override;
	void initializePositions() override;
	void onBeforeStateEnter(GameState* gameState) override;
	void onStateEnter(GameState* gameState) override;
	void onStateReload(GameState* gameState) override;
	void onStateExit(GameState* gameState) override;

private:
	typedef StateBase super;

	SmartAnimationSequenceNode* coinAnimation;
};
