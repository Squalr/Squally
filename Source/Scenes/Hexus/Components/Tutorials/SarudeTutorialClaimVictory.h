#pragma once

#include "Scenes/Hexus/Components/Tutorials/TutorialBase.h"

class FocusTakeOver;
class HelpArrow;
class LocalizedLabel;
class ClickableTextNode;

class SarudeTutorialClaimVictory : public TutorialBase
{
public:
	static SarudeTutorialClaimVictory* create();

protected:
	void onBeforeStateChange(GameState* gameState) override;
	void onAnyStateChange(GameState* gameState) override;

private:
	typedef TutorialBase super;
	SarudeTutorialClaimVictory();
	~SarudeTutorialClaimVictory();

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;
	void initializeCallbacks(GameState* gameState);
	bool tryHijackState(GameState* gameState) override;
	void unHijackState(GameState* gameState) override;
	void runTutorialHandCards(GameState* gameState);

	FocusTakeOver* focusTakeOver;
	LocalizedLabel* claimVictoryLabel;
	ClickableTextNode* tutorialNextButton;
	HelpArrow* helpArrowHandCards;
};
