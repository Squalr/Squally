#pragma once

#include "Scenes/Hexus/Components/Tutorials/TutorialBase.h"

class FocusTakeOver;
class HelpArrow;
class LocalizedLabel;
class ClickableTextNode;

class TutorialBIntroSequence : public TutorialBase
{
public:
	static TutorialBIntroSequence* create();

protected:
	void onBeforeStateChange(GameState* eventCustom) override;
	void onAnyStateChange(GameState* eventCustom) override;

private:
	TutorialBIntroSequence();
	~TutorialBIntroSequence();

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;
	void initializeCallbacks(GameState* gameState);
	bool tryHijackState(GameState* gameState) override;

	void runTutorialScoreTotal(GameState* gameState);
	void runTutorialLastStand(GameState* gameState);
	void runTutorialHandCards(GameState* gameState);
	void concludeTutorial(GameState* gameState);

	FocusTakeOver* focusTakeOver;
	LocalizedLabel* scoreTotalsTutorialLabel;
	LocalizedLabel* lastStandTutorialLabel;
	LocalizedLabel* handCardsTutorialLabel;
	ClickableTextNode* scoreTotalsNextButton;
	ClickableTextNode* lastStandNextButton;
	ClickableTextNode* handCardsNextButton;

	HelpArrow* helpArrowScoreTotals;
	HelpArrow* helpArrowLastStand;
	HelpArrow* helpArrowHandCards;
};
