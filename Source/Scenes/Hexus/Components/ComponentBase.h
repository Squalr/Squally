#pragma once
#include "cocos2d.h"

#include "Engine/Objects/GameObject.h"
#include "Resources.h"
#include "Scenes/Hexus/GameState.h"

using namespace cocos2d;

class ComponentBase : public GameObject
{
protected:
	ComponentBase();
	~ComponentBase();

	void initializeListeners() override;
	virtual void onStateChange(GameState* gameState);

private:
	void onStateChangeEvent(EventCustom* eventCustom);
};
