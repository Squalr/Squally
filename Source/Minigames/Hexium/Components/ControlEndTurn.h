#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include "MiniGames/Hexium/Components/ComponentBase.h"
#include "GUI/Components/MenuSprite.h"
#include "Utils/StrUtils.h"

using namespace cocos2d;

class ControlEndTurn : public ComponentBase
{
public:
	static ControlEndTurn * create();

protected:
	void onStateChange(GameState* gameState) override;

private:
	ControlEndTurn();
	~ControlEndTurn();

	void onEnter() override;
	void initializePositions();
	void initializeListeners();
	void endTurn(GameState* gameState);

	GameState* activeGameState;
};
