#pragma once

#include "Scenes/Hexus/Components/ComponentBase.h"

class ClickableNode;
class ConstantString;
class GameState;
class LocalizedLabel;

class DebugDisplay : public ComponentBase
{
public:
	static DebugDisplay* create();

protected:
	DebugDisplay();
	virtual ~DebugDisplay();

	void onDeveloperModeEnable(int debugLevel) override;
	void onDeveloperModeDisable() override;
	void initializePositions() override;
	void initializeListeners() override;
	void onBeforeStateChange(GameState* gameState) override;
	void onAnyStateChange(GameState* gameState) override;

private:
	typedef ComponentBase super;

	GameState* activeGameState = nullptr;
	ConstantString* stateStr = nullptr;
	LocalizedLabel* stateLabel = nullptr;
	ClickableNode* loseButton = nullptr;
	ClickableNode* drawButton = nullptr;
	ClickableNode* winButton = nullptr;

	static const bool enabled;
};
