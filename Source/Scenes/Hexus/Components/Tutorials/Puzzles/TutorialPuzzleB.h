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
	TutorialPuzzleB();
	virtual ~TutorialPuzzleB();
	
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
\
	FocusTakeOver* focusTakeOver;
	LocalizedLabel* introTutorialLabel;
	LocalizedLabel* decimalCardsTutorialLabel;
	ClickableTextNode* introNextButton;
	ClickableTextNode* decimalCardsNextButton;
};
