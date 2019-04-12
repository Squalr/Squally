#pragma once
#include <functional>

#include "cocos/base/CCEventKeyboard.h"
#include "cocos/base/ccTypes.h"

#include "Engine/SmartNode.h"

namespace cocos2d
{
	class Sprite;
}

class LocalizedLabel;
class ClickableNode;
class ClickableTextNode;

class PauseMenu : public SmartNode
{
public:
	static PauseMenu* create();

	void setResumeCallback(std::function<void()> resumeClickCallback);
	void setOptionsCallback(std::function<void()> optionsClickCallback);
	void setExitCallback(std::function<void()> exitClickCallback);

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
	void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
	void onResumeClick();
	void onOptionsClick();
	void onExitClick();

	cocos2d::Sprite* pauseWindow;
	LocalizedLabel* pauseLabel;
	ClickableNode* closeButton;
	ClickableTextNode* resumeButton;
	ClickableTextNode* optionsButton;
	ClickableTextNode* exitButton;

	std::function<void()> resumeClickCallback;
	std::function<void()> optionsClickCallback;
	std::function<void()> exitClickCallback;

	static const cocos2d::Color3B TitleColor;
};
