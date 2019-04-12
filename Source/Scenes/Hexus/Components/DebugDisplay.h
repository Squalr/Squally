#pragma once

#include "Scenes/Hexus/Components/ComponentBase.h"

class ClickableNode;
class GameState;
class LocalizedLabel;

class DebugDisplay : public ComponentBase
{
public:
	static DebugDisplay* create();

protected:
	void onBeforeStateChange(GameState* gameState) override;
	void onAnyStateChange(GameState* gameState) override;

private:
	typedef ComponentBase super;
	DebugDisplay();
	~DebugDisplay();

	void onDeveloperModeEnable() override;
	void onDeveloperModeDisable() override;
	void initializePositions() override;
	void initializeListeners() override;

	GameState* activeGameState;
	LocalizedLabel* stateLabel;
	ClickableNode* loseButton;
	ClickableNode* drawButton;
	ClickableNode* winButton;

	static const bool enabled;
};
