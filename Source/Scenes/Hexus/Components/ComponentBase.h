#pragma once

#include "Engine/SmartNode.h"

namespace cocos2d
{
	class EventCustom;
}

class GameState;

class ComponentBase : public SmartNode
{
protected:
	ComponentBase();
	~ComponentBase();

	void initializeListeners() override;
	virtual void onBeforeStateChange(GameState* gameState);
	virtual void onAnyRequestStateChange(GameState* gameState);
	virtual void onAnyStateChange(GameState* gameState);

private:
	typedef SmartNode super;
	void onRequestStateChangeEvent(cocos2d::EventCustom* eventCustom);
	void onBeforeStateChangeEvent(cocos2d::EventCustom* eventCustom);
	void onStateChangeEvent(cocos2d::EventCustom* eventCustom);
};
