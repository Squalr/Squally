#pragma once
#include "cocos2d.h"

#include "Engine/Localization/Localization.h"
#include "Engine/UI/Controls/MenuSprite.h"
#include "Engine/Utils/StrUtils.h"
#include "Engine/Sound/SoundManager.h"
#include "Resources.h"
#include "Scenes/Hexus/Components/ComponentBase.h"

using namespace cocos2d;

class ControlSelectionStaged : public ComponentBase
{
public:
	static ControlSelectionStaged * create();

protected:
	void onStateChange(GameState* gameState) override;

private:
	ControlSelectionStaged();
	~ControlSelectionStaged();

	void initializePositions() override;
	void initializeCallbacks(GameState* gameState);
	void aiPerformAction(GameState* gameState);
	void selectCard(Card* card);
	void stageSelectedSacrificeCard(Card* card);
	void stageSelectedCombineCard(Card* card);
	void playSelectedCard(CardRow* cardRow);
	void updateSelectionStatus();
	void onSelectionCancel(MenuSprite* menuSprite);
	void onHelpClick(MenuSprite* menuSprite);

	GameState* activeGameState;
	Label* selectionLabel;
	MenuSprite* cancelButton;
	MenuSprite* helpButton;
};
