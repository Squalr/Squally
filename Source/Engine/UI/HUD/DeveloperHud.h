#pragma once
#include "cocos/base/ccTypes.h"
#include "cocos/base/CCEventKeyboard.h"

#include "Engine/UI/HUD/Hud.h"

class MenuSprite;
class SerializableMap;

namespace cocos2d
{
	class LayerColor;
}

class DeveloperHud : public Hud
{
public:
	static DeveloperHud * create();

	void loadMap(SerializableMap* serializableMapInit);

private:
	DeveloperHud();
	virtual ~DeveloperHud();

	void onEnter() override;
	void initializePositions();
	void initializeListeners();
	void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
	void onSaveClick(MenuSprite* menuSprite);

	SerializableMap* serializableMap;
	cocos2d::LayerColor* layerSelectionBackground;
	MenuSprite* saveButton;

	static const cocos2d::Color4B menuColor;
};
