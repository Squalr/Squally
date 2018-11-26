#pragma once
#include "cocos2d.h"

#include "Engine/Localization/Localization.h"
#include "Engine/Sound/SoundManager.h"
#include "Engine/UI/Controls/TextMenuSprite.h"
#include "Engine/UI/Controls/MenuSprite.h"
#include "Engine/Utils/StrUtils.h"
#include "Events/NavigationEvents.h"
#include "Events/HexusEvents.h"

#include "Scenes/Hexus/States/StateBase.h"

using namespace cocos2d;

class StateGameEnd : public StateBase
{
public:
	static StateGameEnd * create();

protected:
	void onBeforeStateEnter(GameState* gameState) override;
	void onStateEnter(GameState* gameState) override;
	void onStateReload(GameState* gameState) override;
	void onStateExit(GameState* gameState) override;

private:
	StateGameEnd();
	~StateGameEnd();

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;
	void onBackClick(MenuSprite* menuSprite, GameState* gameState);

	TextMenuSprite* backButton;
};
