#pragma once

#include "Scenes/Hexus/Components/Tutorials/TutorialBase.h"

class FocusTakeOver;
class HelpArrow;
class LocalizedLabel;
class TextMenuSprite;

class TutorialAWinningRound : public TutorialBase
{
public:
	static TutorialAWinningRound * create();

protected:
	void onBeforeStateChange(GameState* eventCustom) override;
	void onAnyStateChange(GameState* eventCustom) override;

private:
	TutorialAWinningRound();
	~TutorialAWinningRound();

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;
	void initializeCallbacks(GameState* gameState);
	bool tryHijackState(GameState* gameState) override;

	void runTutorialScoreTotal(GameState* gameState);
	void concludeTutorial(GameState* gameState);

	FocusTakeOver* focusTakeOver;
	LocalizedLabel* scoreTotalsTutorialLabel;
	TextMenuSprite* scoreTotalsNextButton;
	HelpArrow* helpArrowScoreTotals;
};
