#pragma once

#include "Scenes/Hexus/Components/ComponentBase.h"

class LocalizedLabel;
class MenuSprite;

class StagingHelperText : public ComponentBase
{
public:
	static StagingHelperText* create();

protected:
	void onBeforeStateChange(GameState* eventCustom) override;
	void onAnyStateChange(GameState* eventCustom) override;

private:
	StagingHelperText();
	~StagingHelperText();

	void onEnter() override;
	void initializePositions() override;
	void updateSelectionStatus(GameState* gameState);
	void onHelpClick(MenuSprite* menuSprite, GameState* gameState);
	void updateCombineStatus(GameState* gameState);
	void onSelectionCancel(MenuSprite* menuSprite, GameState* gameState);
	void onCombineCancel(MenuSprite* menuSprite, GameState* gameState);
	void clearSelectionStatus();

	LocalizedLabel* selectionLabel;
	MenuSprite* cancelButton;
	MenuSprite* helpButton;
};
