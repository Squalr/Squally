#pragma once
#include "cocos2d.h"

#include "Engine/Maps/SerializableMap.h"
#include "Engine/UI/Controls/MenuSprite.h"
#include "Engine/UI/HUD/Hud.h"
#include "Engine/UI/Mouse.h"
#include "Engine/Utils/GameUtils.h"
#include "Resources.h"

using namespace cocos2d;

class DeveloperHud : public Hud
{
public:
	static DeveloperHud * create();

	void loadMap(SerializableMap* serializableMapInit);

private:
	DeveloperHud();
	~DeveloperHud();

	void onEnter() override;
	void initializePositions();
	void initializeListeners();
	void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
	void onSaveClick(MenuSprite* menuSprite);

	SerializableMap* serializableMap;
	LayerColor* layerSelectionBackground;
	MenuSprite* saveButton;

	static const Color4B menuColor;
};
