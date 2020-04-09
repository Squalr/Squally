#pragma once

#include "Scenes/Hexus/Components/Tutorials/TutorialBase.h"

class FocusTakeOver;
class HelpArrow;
class LocalizedLabel;
class ClickableTextNode;

class TutorialCIntroSequence : public TutorialBase
{
public:
	static TutorialCIntroSequence* create();

protected:
	TutorialCIntroSequence();
	virtual ~TutorialCIntroSequence();

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
	void runTutorialLastStand(GameState* gameState);
	void runTutorialHandCards(GameState* gameState);

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
