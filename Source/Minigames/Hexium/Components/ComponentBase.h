#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include "MiniGames/Hexium/GameState.h"

using namespace cocos2d;

class ComponentBase : public Node
{
public:
	static ComponentBase * create();

protected:
	ComponentBase();
	~ComponentBase();

	virtual void onStateChange(GameState* gameState);
	void onEnter() override;

private:

	void initializePositions();
	void initializeListeners();
	void onStateChange(EventCustom* eventCustom);
};
