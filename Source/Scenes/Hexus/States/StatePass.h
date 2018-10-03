#pragma once
#include "cocos2d.h"

#include "Engine/Localization/Localization.h"
#include "Engine/UI/Controls/MenuSprite.h"
#include "Engine/UI/Controls/TextMenuSprite.h"
#include "Engine/Utils/StrUtils.h"
#include "Resources.h"
#include "Scenes/Hexus/States/StateBase.h"

using namespace cocos2d;

class StatePass : public StateBase
{
public:
	static StatePass * create();

protected:
	void onStateChange(GameState* gameState) override;
	void onBeforeStateEnter(GameState* gameState) override;
	void onStateEnter(GameState* gameState) override;
	void onStateReload(GameState* gameState) override;
	void onStateExit(GameState* gameState) override;

private:
	StatePass();
	~StatePass();

	void initializePositions() override;
	void onPassClick(MenuSprite* menuSprite, GameState* gameState);

	TextMenuSprite* passButton;
	static const std::string StringKeyHexusPass;
};
