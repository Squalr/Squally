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

	FocusTakeOver* focusTakeOver = nullptr;
	LocalizedLabel* scoreTotalsTutorialLabel = nullptr;
	LocalizedLabel* lastStandTutorialLabel = nullptr;
	LocalizedLabel* handCardsTutorialLabel = nullptr;
	ClickableTextNode* scoreTotalsNextButton = nullptr;
	ClickableTextNode* lastStandNextButton = nullptr;
	ClickableTextNode* handCardsNextButton = nullptr;

	HelpArrow* helpArrowScoreTotals = nullptr;
	HelpArrow* helpArrowLastStand = nullptr;
	HelpArrow* helpArrowHandCards = nullptr;
};
