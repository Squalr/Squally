#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include "Engine/Maps/SerializableMap.h"
#include "Engine/Rendering/Components/Mouse.h"
#include "Utils/GameUtils.h"

using namespace cocos2d;

class DeveloperHud : public Node
{
public:
	static DeveloperHud * create();

	void loadLevel(SerializableMap* map);

private:
	DeveloperHud();
	~DeveloperHud();

	void onEnter() override;
	void initializePositions();
	void initializeListeners();
	void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);

	SerializableMap* levelMap;
	LayerColor* layerSelectionBackground;
	static const Color4B menuColor;
};
