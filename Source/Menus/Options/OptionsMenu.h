#pragma once
#include <string>
#include <functional>

#include "cocos/base/ccTypes.h"
#include "cocos/base/CCEventKeyboard.h"

#include "Engine/UI/HUD/Hud.h"

namespace cocos2d
{
	class Node;
	class Sprite;
	class Label;
}

class CCheckbox;
class CRadioButton;
class CSlider;
class LocalizedLabel;
class MenuSprite;
class TextMenuSprite;

class OptionsMenu : public Hud
{
public:
	static OptionsMenu* create();

	void setBackClickCallback(std::function<void()> backClickCallback);

protected:
	OptionsMenu();
	~OptionsMenu();

private:
	void onEnter() override;
	void initializeListeners() override;
	void initializePositions() override;
	void onSoundVolumeUpdate(float soundVolume);
	void onMusicVolumeUpdate(float musicVolume);
	bool onFullScreenChanged(CCheckbox* checkbox, bool isFullScreen);
	void onResolutionChanged(CRadioButton* radioButton);
	void onCloseClick(MenuSprite* menuSprite);
	void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
	void showResolutionOptions();
	void hideResolutionOptions();
	void onMenuExit();

	std::function<void()> backClickCallback;

	cocos2d::Node* background;
	cocos2d::Sprite* optionsWindow;
	LocalizedLabel* optionsLabel;
	MenuSprite* closeButton;

	cocos2d::Sprite* musicIcon;
	cocos2d::Sprite* soundIcon;
	CSlider* musicSlider;
	CSlider* soundSlider;
	LocalizedLabel* fullScreenLabel;
	CCheckbox* fullScreenButton;
	TextMenuSprite* returnButton;

	LocalizedLabel* label1080x768;
	LocalizedLabel* label1152x864;
	LocalizedLabel* label1280x720;
	LocalizedLabel* label1280x960;
	LocalizedLabel* label1280x1024;
	LocalizedLabel* label1440x900;
	LocalizedLabel* label1600x900;
	LocalizedLabel* label1600x1024;
	LocalizedLabel* label1920x1080;
	LocalizedLabel* label2560x1440;
	LocalizedLabel* label3840x2160;

	CRadioButton* option1080x768;
	CRadioButton* option1152x864;
	CRadioButton* option1280x720;
	CRadioButton* option1280x960;
	CRadioButton* option1280x1024;
	CRadioButton* option1440x900;
	CRadioButton* option1600x900;
	CRadioButton* option1600x1024;
	CRadioButton* option1920x1080;
	CRadioButton* option2560x1440;
	CRadioButton* option3840x2160;

	static const cocos2d::Color3B TitleColor;
	static const int ResolutionGroupId;
};

