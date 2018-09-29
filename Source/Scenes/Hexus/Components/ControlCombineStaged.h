#pragma once
#include "cocos2d.h"

#include "Engine/Localization/Localization.h"
#include "Engine/UI/Controls/MenuSprite.h"
#include "Engine/Sound/SoundManager.h"
#include "Engine/Utils/StrUtils.h"
#include "Resources.h"
#include "Scenes/Hexus/Components/ComponentBase.h"

using namespace cocos2d;

class ControlCombineStaged : public ComponentBase
{
public:
	static ControlCombineStaged * create();

protected:
	void onStateChange(GameState* gameState) override;

private:
	ControlCombineStaged();
	~ControlCombineStaged();

	void initializePositions() override;
	void initializeCallbacks(GameState* gameState);
	void aiPerformAction(GameState* gameState);
	void selectCard(Card* card);
	void stageCombineTarget(Card* card);
	void updateCombineStatus();
	void onCombineCancel(MenuSprite* menuSprite);

	GameState* activeGameState;
	Label* combineStatus;
	MenuSprite* cancelButton;
};
