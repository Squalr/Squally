#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include "Engine/Maps/SerializableMap.h"
#include "Engine/Rendering/Components/MenuSprite.h"
#include "Engine/Rendering/Components/Mouse.h"
#include "Engine/Rendering/Components/UILayer.h"
#include "Engine/Utils/GameUtils.h"

using namespace cocos2d;

class DeveloperHud : public UILayer
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
