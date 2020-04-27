#pragma once
#include <functional>

#include "cocos/base/ccTypes.h"

#include "Engine/SmartNode.h"

namespace cocos2d
{
	class Sprite;
}

class ClickableNode;
class ClickableTextNode;
class ConfirmationMenu;
class LocalizedLabel;
class LocalizedString;

class PauseMenu : public SmartNode
{
public:
	static PauseMenu* create();

	void open(std::function<void()> resumeClickCallback);
	void close();
	void setOptionsClickCallback(std::function<void()> optionsClickCallback);
	void setQuitToTitleClickCallback(std::function<void()> quitToTitleClickCallback);
	ClickableTextNode* addNewButton(LocalizedString* text);

protected:
	PauseMenu(bool ownerInitialized = false);
	virtual ~PauseMenu();

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;

	cocos2d::Sprite* pauseWindow;
	LocalizedLabel* pauseLabel;
	ClickableNode* closeButton;
	ClickableTextNode* resumeButton;
	ClickableTextNode* optionsButton;
	ClickableTextNode* quitToTitleButton;
	cocos2d::Node* newButtonsNode;
	std::vector<ClickableTextNode*> addedButtons;
	ConfirmationMenu* exitConfirmMenu;

	std::function<void()> resumeClickCallback;
	std::function<void()> optionsClickCallback;
	std::function<void()> quitToTitleClickCallback;

private:
	typedef SmartNode super;
};
