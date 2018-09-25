#pragma once
#include "cocos2d.h"

#include "Events/NavigationEvents.h"
#include "Engine/UI/Controls/MenuSprite.h"
#include "Engine/UI/Controls/ScrollPane.h"
#include "Engine/UI/FadeScene.h"
#include "Engine/UI/Mouse.h"
#include "Engine/Utils/GameUtils.h"
#include "Resources.h"

using namespace cocos2d;

class HexusDeckManagement : public FadeScene
{
public:
	static HexusDeckManagement * create();

protected:
	HexusDeckManagement();
	~HexusDeckManagement();

private:
	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;
	void onCloseClick(MenuSprite* menuSprite);
	void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);

	Sprite* background;
	ScrollPane* storageScrollPane;
	ScrollPane* deckScrollPane;
};

