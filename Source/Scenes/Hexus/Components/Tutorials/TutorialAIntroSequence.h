#pragma once

#include "Scenes/Hexus/Components/Tutorials/TutorialBase.h"

class FocusTakeOver;
class HelpArrow;
class LocalizedLabel;
class ClickableTextNode;

class TutorialAIntroSequence : public TutorialBase
{
public:
	static TutorialAIntroSequence* create();

protected:
	TutorialAIntroSequence();
	virtual ~TutorialAIntroSequence();
	
	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;
	void onBeforeStateChange(GameState* gameState) override;
	void onAnyStateChange(GameState* gameState) override;
	bool tryHijackState(GameState* gameState) override;
	void unHijackState(GameState* gameState) override;

private:
	typedef TutorialBase super;

	void initializeCallbacks(GameState* gameState);
	void runTutorialScoreTotal(GameState* gameState);
	void runTutorialLossDisplay(GameState* gameState);
	void runTutorialBinaryCards(GameState* gameState);
	void runTutorialDecimalCards(GameState* gameState);
	void runTutorialHexCards(GameState* gameState);
	void runTutorialRowTotals(GameState* gameState);
	void runTutorialHandCards(GameState* gameState);
\
	FocusTakeOver* focusTakeOver = nullptr;
	LocalizedLabel* scoreTotalsTutorialLabel = nullptr;
	LocalizedLabel* lossDisplayTutorialLabel = nullptr;
	LocalizedLabel* binaryCardsTutorialLabel = nullptr;
	LocalizedLabel* decimalCardsTutorialLabel = nullptr;
	LocalizedLabel* hexCardsTutorialLabel = nullptr;
	LocalizedLabel* rowTotalsTutorialLabel = nullptr;
	LocalizedLabel* handCardsTutorialLabel = nullptr;
	ClickableTextNode* scoreTotalsNextButton = nullptr;
	ClickableTextNode* lossDisplayNextButton = nullptr;
	ClickableTextNode* binaryCardsNextButton = nullptr;
	ClickableTextNode* decimalCardsNextButton = nullptr;
	ClickableTextNode* hexCardsNextButton = nullptr;
	ClickableTextNode* rowTotalsNextButton = nullptr;
	ClickableTextNode* handCardsNextButton = nullptr;

	HelpArrow* helpArrowScoreTotals = nullptr;
	HelpArrow* helpArrowLossDisplay = nullptr;
	HelpArrow* helpArrowRowTotals = nullptr;
	HelpArrow* helpArrowHandCards = nullptr;
};
