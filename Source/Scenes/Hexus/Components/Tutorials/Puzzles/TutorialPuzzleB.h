#pragma once

#include "Scenes/Hexus/Components/Tutorials/TutorialBase.h"

class FocusTakeOver;
class HelpArrow;
class LocalizedLabel;
class ClickableTextNode;

class TutorialPuzzleB : public TutorialBase
{
public:
	static TutorialPuzzleB* create();

protected:
	void onBeforeStateChange(GameState* gameState) override;
	void onAnyStateChange(GameState* gameState) override;

private:
	typedef TutorialBase super;
	TutorialPuzzleB();
	~TutorialPuzzleB();

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;
	void initializeCallbacks(GameState* gameState);
	bool tryHijackState(GameState* gameState) override;
	void unHijackState(GameState* gameState) override;
	void runTutorialIntro(GameState* gameState);
	void runTutorialDecimalCards(GameState* gameState);
\
	FocusTakeOver* focusTakeOver;
	LocalizedLabel* introTutorialLabel;
	LocalizedLabel* decimalCardsTutorialLabel;
	ClickableTextNode* introNextButton;
	ClickableTextNode* decimalCardsNextButton;
};
