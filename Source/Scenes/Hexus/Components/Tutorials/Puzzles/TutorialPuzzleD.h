#pragma once

#include "Scenes/Hexus/Components/Tutorials/TutorialBase.h"

class FocusTakeOver;
class HelpArrow;
class LocalizedLabel;
class ClickableTextNode;

class TutorialPuzzleD : public TutorialBase
{
public:
	static TutorialPuzzleD* create();

protected:
	void onBeforeStateChange(GameState* gameState) override;
	void onAnyStateChange(GameState* gameState) override;

private:
	typedef TutorialBase super;
	TutorialPuzzleD();
	~TutorialPuzzleD();

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;
	void initializeCallbacks(GameState* gameState);
	bool tryHijackState(GameState* gameState) override;
	void unHijackState(GameState* gameState) override;
	void runTutorialIntro(GameState* gameState);
\
	FocusTakeOver* focusTakeOver;
	LocalizedLabel* introTutorialLabel;
	ClickableTextNode* introNextButton;
};
