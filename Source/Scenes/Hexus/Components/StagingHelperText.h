#pragma once

#include "Scenes/Hexus/Components/ComponentBase.h"

class LocalizedLabel;
class ClickableNode;

class StagingHelperText : public ComponentBase
{
public:
	static StagingHelperText* create();

protected:
	void onBeforeStateChange(GameState* gameState) override;
	void onAnyStateChange(GameState* gameState) override;

private:
	typedef ComponentBase super;
	StagingHelperText();
	~StagingHelperText();

	void onEnter() override;
	void initializePositions() override;
	void updateSelectionStatus(GameState* gameState);
	void onHelpClick(ClickableNode* menuSprite, GameState* gameState);
	void updateCombineStatus(GameState* gameState);
	void onSelectionCancel(ClickableNode* menuSprite, GameState* gameState);
	void onCombineCancel(ClickableNode* menuSprite, GameState* gameState);
	void clearSelectionStatus();

	LocalizedLabel* selectionLabel;
	ClickableNode* cancelButton;
	ClickableNode* helpButton;
};
