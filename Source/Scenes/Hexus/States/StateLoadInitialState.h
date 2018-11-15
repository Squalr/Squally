#pragma once
#include "cocos2d.h"

#include "Scenes/Hexus/States/StateBase.h"

using namespace cocos2d;

class StateLoadInitialState : public StateBase
{
public:
	static StateLoadInitialState * create();

protected:
	void onBeforeStateEnter(GameState* gameState) override;
	void onStateEnter(GameState* gameState) override;
	void onStateReload(GameState* gameState) override;
	void onStateExit(GameState* gameState) override;

private:
	StateLoadInitialState();
	~StateLoadInitialState();

	void loadStateOverrides(GameState* gameState, StateOverride* stateOverride);
};
