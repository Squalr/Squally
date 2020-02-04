#pragma once

#include "Scenes/Hexus/Components/Tutorials/TutorialBase.h"

class FocusTakeOver;
class HelpArrow;
class LocalizedLabel;
class ClickableTextNode;

class TutorialACardStaged : public TutorialBase
{
public:
	static TutorialACardStaged* create();

protected:
	TutorialACardStaged();
	virtual ~TutorialACardStaged();
	
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

	HelpArrow* binaryCardArrow;
	HelpArrow* decimalCardArrow;
	HelpArrow* hexCardArrow;
};
