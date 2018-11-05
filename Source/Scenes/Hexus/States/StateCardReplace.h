#pragma once
#include "cocos2d.h"

#include "Engine/Localization/Localization.h"
#include "Engine/UI/Controls/TextMenuSprite.h"
#include "Engine/UI/Controls/MenuSprite.h"
#include "Engine/Utils/StrUtils.h"
#include "Resources.h"
#include "Scenes/Hexus/States/StateBase.h"

using namespace cocos2d;

class StateCardReplace : public StateBase
{
public:
	static StateCardReplace * create();

protected:
	void onBeforeStateEnter(GameState* gameState) override;
	void onStateEnter(GameState* gameState) override;
	void onStateReload(GameState* gameState) override;
	void onStateExit(GameState* gameState) override;

private:
	StateCardReplace();
	~StateCardReplace();

	void initializePositions() override;
	void onEndReplaceCards(MenuSprite* menuSprite, GameState* gameState);
	void initializeCallbacks(GameState* gameState);
	void replaceCard(Card* cardToReplace, GameState* gameState);

	std::vector<Card*> removedCards;
	TextMenuSprite* doneButton;
};
