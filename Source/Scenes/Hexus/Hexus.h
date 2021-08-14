#pragma once

#include "Engine/SmartNode.h"

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
class StateSourceCardStaged;
class StateDraw;
class StateDrawInitial;
class StateGameEnd;
class StateGameExit;
class StateLoadInitialState;
class StateGameStart;
class StateNeutral;
class StateOpponentTurnStart;
class StatePlayCard;
class StatePass;
class StatePeekCards;
class StatePlayerTurnStart;
class StateRoundEnd;
class StateRoundStart;
class StateHandCardStaged;
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
class ChallengeBanner;
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

class Avatars;
class CardPreviewComponent;
class Deck;
class AssemblyHelpText;
class StagingHelperText;
class GameState;
class HexusOpponentData;
class HelpMenu;
class Track;

class Hexus : public SmartNode
{
public:
	static Hexus* create();

	void open(HexusOpponentData* opponentData);

private:
	typedef SmartNode super;
	
	Hexus();
	virtual ~Hexus();

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;

	void buildEnemyDeck(HexusOpponentData* opponentData);
	void buildPlayerDeck();

	GameState* gameState = nullptr;
	cocos2d::Sprite* gameBackground = nullptr;

	// GameComponents
	Avatars* avatars = nullptr;
	CardPreviewComponent* cardPreviewComponent = nullptr;
	StagingHelperText* stagingHelperText = nullptr;
	AssemblyHelpText* assemblyHelpText = nullptr;

	StateAIDecideCard* stateAIDecideCard = nullptr;
	StateAIDecideCardReplace* stateAIDecideCardReplace = nullptr;
	StateAIDecidePass* stateAIDecidePass = nullptr;
	StateAIDecideTarget* stateAIDecideTarget = nullptr;
	StateCardReplace* stateCardReplace = nullptr;
	StatePeekCards* statePeekCards = nullptr;
	StateCoinFlip* stateCoinFlip = nullptr;
	StateSourceCardStaged* stateSourceCardStaged = nullptr;
	StateDraw* stateDraw = nullptr;
	StateDrawInitial* stateDrawInitial = nullptr;
	StateGameEnd* stateGameEnd = nullptr;
	StateGameExit* stateGameExit = nullptr;
	StateLoadInitialState* stateLoadInitialState = nullptr;
	StateGameStart* stateGameStart = nullptr;
	StateNeutral* stateNeutral = nullptr;
	StateOpponentTurnStart* stateOpponentTurnStart = nullptr;
	StatePlayCard* statePlayCard = nullptr;
	StatePass* statePass = nullptr;
	StatePlayerTurnStart* statePlayerTurnStart = nullptr;
	StateRoundEnd* stateRoundEnd = nullptr;
	StateRoundStart* stateRoundStart = nullptr;
	StateHandCardStaged* stateHandCardStaged = nullptr;
	StateTurnEnd* stateTurnEnd = nullptr;
	StateTutorial* stateTutorial = nullptr;

	CardReplaceBanner* cardReplaceBanner = nullptr;
	OpponentFirstBanner* opponentFirstBanner = nullptr;
	OpponentLastStandBanner* opponentLastStandBanner = nullptr;
	OpponentPassBanner* opponentPassBanner = nullptr;
	OpponentRoundWinBanner* opponentRoundWinBanner = nullptr;
	OpponentTurnBanner* opponentTurnBanner = nullptr;
	PlayerFirstBanner* playerFirstBanner = nullptr;
	PlayerLastStandBanner* playerLastStandBanner = nullptr;
	PlayerPassBanner* playerPassBanner = nullptr;
	PlayerRoundWinBanner* playerRoundWinBanner = nullptr;
	PlayerTurnBanner* playerTurnBanner = nullptr;
	ChallengeBanner* challengeBanner = nullptr;
	RoundBanner* roundBanner = nullptr;
	RoundTieBanner* roundTieBanner = nullptr;
	VictoryBanner* victoryBanner = nullptr;
	DefeatBanner* defeatBanner = nullptr;
	DrawBanner* drawBanner = nullptr;

	ClickableNode* boardSelection = nullptr;
	DeckCardCountDisplay* deckCardCountDisplay = nullptr;
	HandCardCountDisplay* handCardCountDisplay = nullptr;
	RemainingCardDisplay* remainingCardDisplay = nullptr;
	DrawCountDisplay* drawCountDisplay = nullptr;
	LossesDisplay* lossesDisplay = nullptr;
	RowTotals* rowTotals = nullptr;
	ScoreTotal* scoreTotal = nullptr;
	DebugDisplay* debugDisplay = nullptr;

	cocos2d::Node* tutorialLayer = nullptr;
	cocos2d::Node* relocateLayer = nullptr;

	cocos2d::LayerColor* menuBackDrop = nullptr;
	HelpMenu* helpMenu = nullptr;

	Track* musicA = nullptr;
	Track* musicB = nullptr;

	static Hexus* instance;
};
