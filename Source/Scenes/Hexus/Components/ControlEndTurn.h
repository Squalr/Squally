#pragma once
#include "cocos2d.h"

#include "Engine/UI/Controls/MenuSprite.h"
#include "Engine/Utils/StrUtils.h"
#include "Resources.h"
#include "Scenes/Hexus/Components/ComponentBase.h"

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

	void endTurn(GameState* gameState);

	GameState* activeGameState;
};
