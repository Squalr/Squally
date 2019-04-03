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
	void updateCombineStatus(GameState* gameState);
	void onSelectionCancel(GameState* gameState);
	void onCombineCancel(GameState* gameState);
	void clearSelectionStatus();

	LocalizedLabel* selectionLabel;
	ClickableNode* cancelButton;
};
