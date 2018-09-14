#pragma once
#include "cocos2d.h"

#include "Engine/Localization/Localization.h"
#include "Engine/Rendering/Components/MenuSprite.h"
#include "Engine/Utils/StrUtils.h"
#include "Resources.h"

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

	void initializePositions() override;
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
