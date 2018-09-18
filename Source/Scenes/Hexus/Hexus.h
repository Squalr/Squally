#pragma once
#include "cocos2d.h"

#include "Events/NavigationEvents.h"
#include "Events/HexusEvents.h"
#include "Engine/UI/Controls/MenuSprite.h"
#include "Engine/UI/FadeScene.h"
#include "Engine/Utils/StrUtils.h"
#include "Resources.h"
#include "Scenes/Hexus/Components/Components.h"
#include "Scenes/Hexus/GameState.h"

using namespace cocos2d;

class Hexus : public FadeScene
{
public:
	static Hexus * create();

	void onGameStart(EventCustom* eventCustom);

private:
	Hexus();
	~Hexus();

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;
	void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
	void onClose(MenuSprite* menuSprite);

	GameState* gameState;
	Sprite* gameBackground;

	// Components
	Avatars* avatars;
	Banners* banners;
	CardPreview* cardPreview;
	CoinFlip* coinFlip;
	ControlDraw* controlDraw;
	ControlNeutral* controlNeutral;
	ControlEndTurn* controlEndTurn;
	ControlSacrificeStaged* controlSacrificeStaged;
	ControlSelectionStaged* controlSelectionStaged;
	ControlCombineStaged* controlCombineStaged;
	ControlReplaceCards* controlReplaceCards;
	DeckCardCountDisplay* deckCardCountDisplay;
	HandCardCountDisplay* handCardCountDisplay;
	LossesDisplay* lossesDisplay;
	PassButton* passButton;
	RowTotals* rowTotals;
	ScoreTotal* scoreTotal;
};
