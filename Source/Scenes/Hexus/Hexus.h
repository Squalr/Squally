#pragma once
#include "cocos2d.h"

#include "Events/NavigationEvents.h"
#include "Events/HexusEvents.h"
#include "Engine/UI/Controls/MenuSprite.h"
#include "Engine/UI/FadeScene.h"
#include "Engine/Utils/StrUtils.h"
#include "Resources.h"
#include "Scenes/Hexus/CardStorage.h"
#include "Scenes/Hexus/GameState.h"
#include "Scenes/Hexus/Components/Components.h"
#include "Scenes/Hexus/States/States.h"

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
	CardReplaceBanner* cardReplaceBanner;
	OpponentFirstBanner* opponentFirstBanner;
	OpponentTurnBanner* opponentTurnBanner;
	PlayerFirstBanner* playerFirstBanner;
	PlayerTurnBanner* playerTurnBanner;
	RoundBanner* roundBanner;
	VictoryBanner* victoryBanner;
	DefeatBanner* defeatBanner;
	CardPreview* cardPreview;
	StateCoinFlip* stateCoinFlip;
	StateDrawInitial* stateDrawInitial;
	StateDraw* stateDraw;
	StateNeutral* stateNeutral;
	StateTurnEnd* stateTurnEnd;
	StateSelectionStaged* stateSelectionStaged;
	StateCombineStaged* stateCombineStaged;
	StateReplaceCards* stateReplaceCards;
	StateGameEnd* stateGameEnd;
	DeckCardCountDisplay* deckCardCountDisplay;
	HandCardCountDisplay* handCardCountDisplay;
	LossesDisplay* lossesDisplay;
	PassButton* passButton;
	RowTotals* rowTotals;
	ScoreTotal* scoreTotal;
};
