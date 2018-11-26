#pragma once
#include "cocos2d.h"

#include "Engine/Localization/Localization.h"
#include "Engine/UI/Controls/MenuSprite.h"
#include "Engine/Utils/StrUtils.h"
#include "Resources/UIResources.h"
#include "Scenes/Hexus/Components/ComponentBase.h"

using namespace cocos2d;

class StagingHelperText : public ComponentBase
{
public:
	static StagingHelperText * create();

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

	Label* selectionLabel;
	MenuSprite* cancelButton;
	MenuSprite* helpButton;
};
