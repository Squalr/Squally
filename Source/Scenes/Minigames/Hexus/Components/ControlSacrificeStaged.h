#pragma once
#include "cocos2d.h"

#include "Engine/Rendering/Components/MenuSprite.h"
#include "Resources.h"
#include "Utils/StrUtils.h"

#include "ComponentBase.h"

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
	void aiPerformAction(GameState* gameState);
	void selectCard(Card* card);
	void stageSacrificeTarget(Card* card);
	void updateSacrificeStatus();
	void onSacrificeCancel(MenuSprite* menuSprite);

	GameState* activeGameState;
	Label* sacrificeStatus;
	MenuSprite* cancelButton;
};
