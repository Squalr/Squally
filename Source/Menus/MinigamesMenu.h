#pragma once
#include "cocos/base/CCEvent.h"
#include "cocos/base/CCEventKeyboard.h"

#include "Engine/GlobalScene.h"

class MenuSprite;
class TextMenuSprite;
class ScrollPane;

class MinigamesMenu : public GlobalScene
{
public:
	static void registerGlobalScene();

protected:
	MinigamesMenu();
	~MinigamesMenu();

private:
	typedef GlobalScene super;
	void onEnter() override;
	void initializeListeners() override;
	void initializePositions() override;

	void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
	void onBackClick(MenuSprite* menuSprite);
	void onHexusClick(MenuSprite* menuSprite);
	void onHexusPuzzlesClick(MenuSprite* menuSprite);
	TextMenuSprite* createComingSoonButton();

	cocos2d::Node* backgroundNode;
	ScrollPane* scrollPane;
	TextMenuSprite* hexusButton;
	TextMenuSprite* hexusPuzzlesButton;
	TextMenuSprite* comingSoonButton1;
	TextMenuSprite* comingSoonButton2;
	TextMenuSprite* comingSoonButton3;
	TextMenuSprite* comingSoonButton4;
	TextMenuSprite* comingSoonButton5;
	TextMenuSprite* comingSoonButton6;
	TextMenuSprite* backButton;

	static MinigamesMenu* instance;
};
