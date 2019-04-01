#pragma once
#include "cocos/base/CCEventKeyboard.h"

#include "Engine/GlobalScene.h"

namespace cocos2d
{
	class LayerColor;
	class Sprite;
}

class ClickableNode;

class StateAIDecideCard;
class StateAIDecideCardReplace;
class StateAIDecidePass;
class StateAIDecideTarget;
class StateCardReplace;
class StateCoinFlip;
class StateCombineStaged;
class StateDraw;
class StateDrawInitial;
class StateGameEnd;
class StateLoadInitialState;
class StateGameStart;
class StateNeutral;
class StateOpponentTurnStart;
class StatePlayCard;
class StatePass;
class StatePlayerTurnStart;
class StateRoundEnd;
class StateRoundStart;
class StateSelectionStaged;
class StateTurnEnd;
class StateTutorial;

class CardReplaceBanner;
class OpponentFirstBanner;
class OpponentLastStandBanner;
class OpponentPassBanner;
class OpponentRoundWinBanner;
class OpponentTurnBanner;
class PlayerFirstBanner;
class PlayerLastStandBanner;
class PlayerPassBanner;
class PlayerRoundWinBanner;
class PlayerTurnBanner;
class RoundBanner;
class RoundTieBanner;
class VictoryBanner;
class DefeatBanner;
class DrawBanner;
class DeckCardCountDisplay;
class HandCardCountDisplay;
class RemainingCardDisplay;
class DrawCountDisplay;
class LossesDisplay;
class RowTotals;
class ScoreTotal;
class DebugDisplay;

class TutorialAIntroSequence;
class TutorialAVictory;
class TutorialAWinningRound;
class TutorialBIntroSequence;
class TutorialCIntroSequence;
class TutorialDIntroSequence;
class TutorialEIntroSequence;
class TutorialFIntroSequence;

class Avatars;
class CardPreview;
class StagingHelperText;
class GameState;
class HexusOpponentData;
class PauseMenu;
class OptionsMenu;
class ConfirmationMenu;

class Hexus : public GlobalScene
{
public:
	static void registerGlobalScene();

private:
	typedef GlobalScene super;
	Hexus();
	~Hexus();

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;
	void startGame(HexusOpponentData* opponentData);
	void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
	void onOptionsExit();
	void openPauseMenu();
	void onResumeClick();
	void onOptionsClick();
	void onExitClick();

	GameState* gameState;
	cocos2d::Sprite* gameBackground;

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

	ClickableNode* boardSelection;
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
	TutorialBIntroSequence* tutorialBIntroSequence;
	TutorialCIntroSequence* tutorialCIntroSequence;
	TutorialDIntroSequence* tutorialDIntroSequence;
	TutorialEIntroSequence* tutorialEIntroSequence;
	TutorialFIntroSequence* tutorialFIntroSequence;

	cocos2d::LayerColor* menuBackDrop;
	PauseMenu* pauseMenu;
	OptionsMenu* optionsMenu;
	ConfirmationMenu* confirmationMenu;

	static Hexus* instance;
};
