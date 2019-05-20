#pragma once
#include "cocos/base/CCEventKeyboard.h"

#include "Engine/GlobalScene.h"

namespace cocos2d
{
	class LayerColor;
}

class ClickableNode;
class ClickableTextNode;
class ConfirmationMenu;

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
	void buildSaveButtons();
	ClickableTextNode* buildSaveButton(int profileId);
	ClickableNode* buildDeleteButton(int profileId);
	void loadSave();
	void onBackClick();

	cocos2d::Node* backgroundNode;
	cocos2d::Node* buttonsNode;
	ClickableTextNode* saveGameButton0;
	ClickableTextNode* saveGameButton1;
	ClickableTextNode* saveGameButton2;
	ClickableTextNode* backButton;
	cocos2d::LayerColor* backdrop;
	ConfirmationMenu* confirmationMenu;

	static SaveSelectMenu* instance;
};
