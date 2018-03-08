#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include "MiniGames/Hexium/Components/ComponentBase.h"
#include "GUI/Components/MenuSprite.h"
#include "Utils/StrUtils.h"

using namespace cocos2d;

class ControlSacrificeStaged : public ComponentBase
{
public:
	static ControlSacrificeStaged * create();

protected:
	void onStateChange(GameState* gameState) override;

private:
	ControlSacrificeStaged();
	~ControlSacrificeStaged();

	void onEnter() override;
	void initializePositions();
	void initializeListeners();
	void initializeCallbacks(GameState* gameState);
	void selectCard(Card* card);

	GameState* activeGameState;
};
