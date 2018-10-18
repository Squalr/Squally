#pragma once
#include "cocos2d.h"

#include "Engine/Localization/Localization.h"
#include "Engine/UI/Controls/MenuSprite.h"
#include "Engine/Sound/SoundManager.h"
#include "Engine/Utils/StrUtils.h"
#include "Resources.h"
#include "Scenes/Hexus/States/StateBase.h"

using namespace cocos2d;

class StateCombineStaged : public StateBase
{
public:
	static StateCombineStaged * create();

protected:
	void onBeforeStateEnter(GameState* gameState) override;
	void onStateEnter(GameState* gameState) override;
	void onStateReload(GameState* gameState) override;
	void onStateExit(GameState* gameState) override;

private:
	StateCombineStaged();
	~StateCombineStaged();

	void initializePositions() override;
	void initializeCallbacks(GameState* gameState);
	void aiPerformAction(GameState* gameState);
	void selectCard(Card* card, GameState* gameState);
	void stageCombineTarget(Card* card, GameState* gameState);
	void updateCombineStatus(GameState* gameState);
	void onCombineCancel(MenuSprite* menuSprite, GameState* gameState);

	Label* combineStatus;
	MenuSprite* cancelButton;
};
