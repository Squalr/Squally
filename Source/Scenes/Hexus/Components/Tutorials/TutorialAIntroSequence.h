#pragma once

#include "Scenes/Hexus/Components/Tutorials/TutorialBase.h"

class FocusTakeOver;
class HelpArrow;
class LocalizedLabel;
class TextMenuSprite;

class TutorialAIntroSequence : public TutorialBase
{
public:
	static TutorialAIntroSequence* create();

protected:
	void onBeforeStateChange(GameState* eventCustom) override;
	void onAnyStateChange(GameState* eventCustom) override;

private:
	TutorialAIntroSequence();
	~TutorialAIntroSequence();

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;
	void initializeCallbacks(GameState* gameState);
	bool tryHijackState(GameState* gameState) override;

	void runTutorialScoreTotal(GameState* gameState);
	void runTutorialLossDisplay(GameState* gameState);
	void runTutorialBinaryCards(GameState* gameState);
	void runTutorialDecimalCards(GameState* gameState);
	void runTutorialHexCards(GameState* gameState);
	void runTutorialRowTotals(GameState* gameState);
	void runTutorialHandCards(GameState* gameState);
	void concludeTutorial(GameState* gameState);

	FocusTakeOver* focusTakeOver;
	LocalizedLabel* scoreTotalsTutorialLabel;
	LocalizedLabel* lossDisplayTutorialLabel;
	LocalizedLabel* binaryCardsTutorialLabel;
	LocalizedLabel* decimalCardsTutorialLabel;
	LocalizedLabel* hexCardsTutorialLabel;
	LocalizedLabel* rowTotalsTutorialLabel;
	LocalizedLabel* handCardsTutorialLabel;
	TextMenuSprite* scoreTotalsNextButton;
	TextMenuSprite* lossDisplayNextButton;
	TextMenuSprite* binaryCardsNextButton;
	TextMenuSprite* decimalCardsNextButton;
	TextMenuSprite* hexCardsNextButton;
	TextMenuSprite* rowTotalsNextButton;
	TextMenuSprite* handCardsNextButton;

	HelpArrow* helpArrowScoreTotals;
	HelpArrow* helpArrowLossDisplay;
	HelpArrow* helpArrowRowTotals;
	HelpArrow* helpArrowHandCards;
};
