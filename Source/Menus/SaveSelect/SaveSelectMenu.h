#pragma once

#include "Engine/GlobalScene.h"

namespace cocos2d
{
	class LayerColor;
	class Sprite;
}

class ClickableNode;
class ClickableTextNode;
class ConfirmationMenu;

class SaveSelectMenu : public GlobalScene
{
public:
	static SaveSelectMenu* getInstance();

protected:
	SaveSelectMenu();
	~SaveSelectMenu();

private:
	typedef GlobalScene super;
	void onEnter() override;
	void initializeListeners() override;
	void initializePositions() override;

	void buildSaveButtons();
	ClickableTextNode* buildSaveButton(int profileId);
	ClickableNode* buildDeleteButton(int profileId);
	void loadSave();
	void goBack();

	cocos2d::Node* backgroundNode;
	cocos2d::Sprite* saveSelectWindow;
	cocos2d::Node* saveButtonNode;
	ClickableTextNode* saveGameButton0;
	ClickableTextNode* saveGameButton1;
	ClickableTextNode* saveGameButton2;
	ClickableNode* closeButton;
	ClickableTextNode* returnButton;
	cocos2d::LayerColor* backdrop;
	ConfirmationMenu* confirmationMenu;

	static SaveSelectMenu* instance;
};
