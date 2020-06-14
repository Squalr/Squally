#pragma once

#include "Scenes/Hexus/Components/Tutorials/TutorialBase.h"

class FocusTakeOver;
class HelpArrow;
class LocalizedLabel;
class ClickableTextNode;

class TutorialPuzzleOverflow : public TutorialBase
{
public:
	static TutorialPuzzleOverflow* create();

protected:
	TutorialPuzzleOverflow();
	virtual ~TutorialPuzzleOverflow();
	
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
	void runTutorialIntro(GameState* gameState);
	void runTutorialDecimalCards(GameState* gameState);
	void runTutorialHelp(GameState* gameState);

	FocusTakeOver* focusTakeOver;
	LocalizedLabel* introTutorialLabel;
	LocalizedLabel* decimalCardsTutorialLabel;
	LocalizedLabel* helpTutorialLabel;
	ClickableTextNode* introNextButton;
	ClickableTextNode* decimalCardsNextButton;
	ClickableTextNode* helpNextButton;

	HelpArrow* helpArrow;
};
