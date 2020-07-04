#pragma once

#include "Engine/SmartNode.h"
#include "Scenes/Hexus/GameState.h"

namespace cocos2d
{
	class EventCustom;
}

class StateBase : public SmartNode
{
protected:
	StateBase(GameState::StateType stateType);
	virtual ~StateBase();

	void initializeListeners() override;
	virtual void onAnyStateChange(GameState* gameState);
	virtual void onAnyRequestStateChange(GameState* gameState);
	virtual void onAfterAnyStateChange(GameState* gameState);
	virtual void onBeforeStateEnter(GameState* gameState);
	virtual void onStateEnter(GameState* gameState);
	virtual void onAfterStateEnter(GameState* gameState);
	virtual void onStateReload(GameState* gameState);
	virtual void onStateExit(GameState* gameState);

private:
	typedef SmartNode super;
	void onRequestStateChangeEvent(cocos2d::EventCustom* eventCustom);
	void onBeforeStateChangeEvent(cocos2d::EventCustom* eventCustom);
	void onStateChangeEvent(cocos2d::EventCustom* eventCustom);
	void onAfterStateChangeEvent(cocos2d::EventCustom* eventCustom);

	GameState::StateType stateType;
	float enterDelay;
};
