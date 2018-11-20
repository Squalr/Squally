#pragma once
#include "cocos2d.h"

#include "Engine/SmartNode.h"
#include "Resources.h"
#include "Scenes/Hexus/GameState.h"

using namespace cocos2d;

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
	void onRequestStateChangeEvent(EventCustom* eventCustom);
	void onBeforeStateChangeEvent(EventCustom* eventCustom);
	void onStateChangeEvent(EventCustom* eventCustom);
};
