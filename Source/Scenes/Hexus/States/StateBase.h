#pragma once
#include "cocos2d.h"

#include "Engine/SmartNode.h"
#include "Resources.h"
#include "Scenes/Hexus/GameState.h"

using namespace cocos2d;

class StateBase : public SmartNode
{
protected:
	StateBase(GameState::StateType stateType);
	~StateBase();

	void initializeListeners() override;
	virtual void onStateChange(GameState* gameState);
	virtual void onBeforeStateEnter(GameState* gameState);
	virtual void onStateEnter(GameState* gameState);
	virtual void onStateReload(GameState* gameState);
	virtual void onStateExit(GameState* gameState);

private:
	void onBeforeStateChangeEvent(EventCustom* eventCustom);
	void onStateChangeEvent(EventCustom* eventCustom);

	GameState::StateType stateType;
	float enterDelay;
};
