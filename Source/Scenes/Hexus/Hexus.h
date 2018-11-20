#pragma once
#include "cocos2d.h"

#include "Events/NavigationEvents.h"
#include "Events/HexusEvents.h"
#include "Engine/UI/Controls/MenuSprite.h"
#include "Engine/UI/FadeScene.h"
#include "Engine/Utils/StrUtils.h"
#include "Menus/Confirmation/ConfirmationMenu.h"
#include "Menus/Options/OptionsMenu.h"
#include "Menus/Pause/PauseMenu.h"
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
	void onOptionsExit();
	void openPauseMenu();
	void onResumeClick();
	void onOptionsClick();
	void onExitClick();

	GameState* gameState;
	Sprite* gameBackground;

	// Components
	Avatars* avatars;
	CardPreview* cardPreview;
	StagingHelperText* stagingHelperText;

	StateAIDecideCard* stateAIDecideCard;
	StateAIDecideCardReplace* stateAIDecideCardReplace;
	StateAIDecidePass* stateAIDecidePass;
	StateAIDecideTarget* stateAIDecideTarget;
	StateCardReplace* stateCardReplace;
	StateCoinFlip* stateCoinFlip;
	StateCombineStaged* stateCombineStaged;
	StateDraw* stateDraw;
	StateDrawInitial* stateDrawInitial;
	StateGameEnd* stateGameEnd;
	StateLoadInitialState* stateLoadInitialState;
	StateGameStart* stateGameStart;
	StateNeutral* stateNeutral;
	StateOpponentTurnStart* stateOpponentTurnStart;
	StatePlayCard* statePlayCard;
	StatePass* statePass;
	StatePlayerTurnStart* statePlayerTurnStart;
	StateRoundEnd* stateRoundEnd;
	StateRoundStart* stateRoundStart;
	StateSelectionStaged* stateSelectionStaged;
	StateTurnEnd* stateTurnEnd;
	StateTutorial* stateTutorial;

	CardReplaceBanner* cardReplaceBanner;
	OpponentFirstBanner* opponentFirstBanner;
	OpponentLastStandBanner* opponentLastStandBanner;
	OpponentPassBanner* opponentPassBanner;
	OpponentRoundWinBanner* opponentRoundWinBanner;
	OpponentTurnBanner* opponentTurnBanner;
	PlayerFirstBanner* playerFirstBanner;
	PlayerLastStandBanner* playerLastStandBanner;
	PlayerPassBanner* playerPassBanner;
	PlayerRoundWinBanner* playerRoundWinBanner;
	PlayerTurnBanner* playerTurnBanner;
	RoundBanner* roundBanner;
	RoundTieBanner* roundTieBanner;
	VictoryBanner* victoryBanner;
	DefeatBanner* defeatBanner;
	DrawBanner* drawBanner;

	DeckCardCountDisplay* deckCardCountDisplay;
	HandCardCountDisplay* handCardCountDisplay;
	RemainingCardDisplay* remainingCardDisplay;
	DrawCountDisplay* drawCountDisplay;
	LossesDisplay* lossesDisplay;
	RowTotals* rowTotals;
	ScoreTotal* scoreTotal;
	DebugDisplay* debugDisplay;

	TutorialAIntroSequence* tutorialAIntroSequence;
	TutorialAVictory* tutorialAVictory;
	TutorialAWinningRound* tutorialAWinningRound;

	LayerColor* menuBackDrop;
	PauseMenu* pauseMenu;
	OptionsMenu* optionsMenu;
	ConfirmationMenu* confirmationMenu;
};
