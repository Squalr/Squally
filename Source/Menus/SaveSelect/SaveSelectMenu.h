#pragma once
#include "cocos/base/CCEventKeyboard.h"

#include "Engine/GlobalScene.h"

class MenuSprite;
class TextMenuSprite;

class SaveSelectMenu : public GlobalScene
{
public:
	static void registerGlobalScene();

protected:
	SaveSelectMenu();
	~SaveSelectMenu();

private:
	typedef GlobalScene super;
	void onEnter() override;
	void initializeListeners() override;
	void initializePositions() override;

	void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
	void onSaveGame1Click(MenuSprite* menuSprite);
	void onSaveGame2Click(MenuSprite* menuSprite);
	void onSaveGame3Click(MenuSprite* menuSprite);
	void onBackClick(MenuSprite* menuSprite);

	cocos2d::Node* backgroundNode;
	TextMenuSprite* saveGame1;
	TextMenuSprite* saveGame2;
	TextMenuSprite* saveGame3;
	TextMenuSprite* backButton;

	static SaveSelectMenu* instance;
};
