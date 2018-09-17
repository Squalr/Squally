#pragma once
#include "cocos2d.h"

#include "Engine/Localization/Localization.h"
#include "Engine/UI/Controls/TextMenuSprite.h"
#include "Resources.h"
#include "Scenes/Hexus/Components/ComponentBase.h"

using namespace cocos2d;

class PassButton : public ComponentBase
{
public:
	static PassButton * create();

protected:
	void onStateChange(GameState* gameState) override;

private:
	PassButton();
	~PassButton();

	void initializePositions() override;
	void onPassClick(MenuSprite* menuSprite, GameState* gameState);

	TextMenuSprite* passButton;
	static const std::string StringKeyHexusPass;
};
