#pragma once
#include "cocos/base/CCEventKeyboard.h"

#include "Engine/GlobalScene.h"

class ClickableNode;
class ClickableTextNode;

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
	void onSaveGame1Click();
	void onSaveGame2Click();
	void onSaveGame3Click();
	void onBackClick();

	cocos2d::Node* backgroundNode;
	ClickableTextNode* saveGame1;
	ClickableTextNode* saveGame2;
	ClickableTextNode* saveGame3;
	ClickableTextNode* backButton;

	static SaveSelectMenu* instance;
};
