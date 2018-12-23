#pragma once
#include "cocos/base/CCEvent.h"
#include "cocos/base/CCEventKeyboard.h"

#include "Engine/GlobalScene.h"

class MenuSprite;

class SaveSelectMenu : public GlobalScene
{
public:
	static void registerGlobalScene();

protected:
	SaveSelectMenu();
	~SaveSelectMenu();

private:
	void onEnter() override;
	void initializeListeners() override;
	void initializePositions() override;

	void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
	void onSaveGame1Click(MenuSprite* menuSprite);
	void onSaveGame2Click(MenuSprite* menuSprite);
	void onSaveGame3Click(MenuSprite* menuSprite);

	cocos2d::Node* backgroundNode;
	TextMenuSprite* saveGame1;
	TextMenuSprite* saveGame2;
	TextMenuSprite* saveGame3;

	static SaveSelectMenu* instance;
};

