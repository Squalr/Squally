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

	void setResumeCallback(std::function<void()> resumeClickCallback);
	void setOptionsCallback(std::function<void()> optionsClickCallback);
	void setExitCallback(std::function<void()> exitClickCallback);
	ClickableTextNode* addNewButton(LocalizedString* text);

protected:
	PauseMenu();
	~PauseMenu();

private:
	typedef SmartNode super;
	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;
	void onExitConfirm();
	void onCloseClick();
	void onResumeClick();
	void onOptionsClick();
	void onExitClick();

	cocos2d::Sprite* pauseWindow;
	LocalizedLabel* pauseLabel;
	ClickableNode* closeButton;
	ClickableTextNode* resumeButton;
	ClickableTextNode* optionsButton;
	ClickableTextNode* exitButton;
	cocos2d::Node* newButtonsNode;
	std::vector<ClickableTextNode*> addedButtons;
	ConfirmationMenu* exitConfirmMenu;

	std::function<void()> resumeClickCallback;
	std::function<void()> optionsClickCallback;
	std::function<void()> exitClickCallback;
};
