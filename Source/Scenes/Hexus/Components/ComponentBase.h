#pragma once
#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/GameState.h"

using namespace cocos2d;

class ComponentBase : public Node
{
protected:
	ComponentBase();
	~ComponentBase();

	virtual void onStateChange(GameState* gameState);
	void onEnter() override;

private:

	void initializePositions();
	void initializeListeners();
	void onStateChangeEvent(EventCustom* eventCustom);
};
