#pragma once
#include "cocos2d.h"

#include "Engine/Localization/Localization.h"
#include "Engine/Sound/SoundManager.h"
#include "Engine/UI/Controls/TextMenuSprite.h"
#include "Engine/UI/Controls/MenuSprite.h"
#include "Engine/Utils/StrUtils.h"
#include "Events/NavigationEvents.h"
#include "Events/HexusEvents.h"
#include "Resources.h"
#include "Scenes/Hexus/Components/ComponentBase.h"

using namespace cocos2d;

class ControlGameEnd : public ComponentBase
{
public:
	static ControlGameEnd * create();

protected:
	void onStateChange(GameState* gameState) override;

private:
	ControlGameEnd();
	~ControlGameEnd();

	void initializePositions() override;
	void initializeListeners() override;
	void onBackClick(MenuSprite* menuSprite);

	GameState* activeGameState;
	TextMenuSprite* backButton;
};
