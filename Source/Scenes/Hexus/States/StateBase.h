#pragma once

#include "Engine/SmartNode.h"
#include "Scenes/Hexus/GameState.h"

class StateBase : public SmartNode
{
protected:
	StateBase(GameState::StateType stateType);
	~StateBase();

	void initializeListeners() override;
	virtual void onAnyStateChange(GameState* gameState);
	virtual void onAnyRequestStateChange(GameState* gameState);
	virtual void onBeforeStateEnter(GameState* gameState);
	virtual void onStateEnter(GameState* gameState);
	virtual void onStateReload(GameState* gameState);
	virtual void onStateExit(GameState* gameState);

private:
	void onRequestStateChangeEvent(EventCustom* eventCustom);
	void onBeforeStateChangeEvent(EventCustom* eventCustom);
	void onStateChangeEvent(EventCustom* eventCustom);

	GameState::StateType stateType;
	float enterDelay;
};
