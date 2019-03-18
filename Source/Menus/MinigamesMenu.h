#pragma once
#include "cocos/base/CCEvent.h"
#include "cocos/base/CCEventKeyboard.h"

#include "Engine/GlobalScene.h"

class ClickableNode;
class ClickableTextNode;
class LocalizedString;
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
	void onBackClick(ClickableNode* menuSprite);
	void onHexusClick(ClickableNode* menuSprite);
	void onHexusPuzzlesClick(ClickableNode* menuSprite);
	ClickableTextNode* createButton(LocalizedString* text, std::string iconResource);
	ClickableTextNode* createComingSoonButton();

	cocos2d::Node* backgroundNode;
	ScrollPane* scrollPane;
	ClickableTextNode* hexusButton;
	ClickableTextNode* hexusPuzzlesButton;
	ClickableTextNode* cipherButton;
	ClickableTextNode* comingSoonButton2;
	ClickableTextNode* comingSoonButton3;
	ClickableTextNode* comingSoonButton4;
	ClickableTextNode* comingSoonButton5;
	ClickableTextNode* comingSoonButton6;
	ClickableTextNode* backButton;

	static MinigamesMenu* instance;
};
