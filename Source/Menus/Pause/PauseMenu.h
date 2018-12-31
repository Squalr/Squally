#pragma once
#include <functional>

#include "cocos/base/CCEventKeyboard.h"
#include "cocos/base/ccTypes.h"

#include "Engine/UI/HUD/Hud.h"

namespace cocos2d
{
	class Sprite;
}

class LocalizedLabel;
class MenuSprite;
class TextMenuSprite;

class PauseMenu : public Hud
{
public:
	static PauseMenu * create();

	void setResumeCallback(std::function<void()> resumeClickCallback);
	void setOptionsCallback(std::function<void()> optionsClickCallback);
	void setExitCallback(std::function<void()> exitClickCallback);

protected:
	PauseMenu();
	~PauseMenu();

private:
	typedef Hud super;
	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;
	void onExitConfirm();
	void onCloseClick(MenuSprite* menuSprite);
	void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
	void onResumeClick(MenuSprite* menuSprite);
	void onOptionsClick(MenuSprite* menuSprite);
	void onExitClick(MenuSprite* menuSprite);

	cocos2d::Sprite* pauseWindow;
	LocalizedLabel* pauseLabel;
	MenuSprite* closeButton;
	TextMenuSprite* resumeButton;
	TextMenuSprite* optionsButton;
	TextMenuSprite* exitButton;

	std::function<void()> resumeClickCallback;
	std::function<void()> optionsClickCallback;
	std::function<void()> exitClickCallback;

	static const cocos2d::Color3B TitleColor;
};
