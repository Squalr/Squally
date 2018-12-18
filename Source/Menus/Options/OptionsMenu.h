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
	cocos2d::Label* titleLabel;
	MenuSprite* closeButton;

	cocos2d::Sprite* musicIcon;
	cocos2d::Sprite* soundIcon;
	CSlider* musicSlider;
	CSlider* soundSlider;
	cocos2d::Label* fullScreenLabel;
	CCheckbox* fullScreenButton;
	TextMenuSprite* returnButton;

	cocos2d::Label* label1080x768;
	cocos2d::Label* label1152x864;
	cocos2d::Label* label1280x720;
	cocos2d::Label* label1280x960;
	cocos2d::Label* label1280x1024;
	cocos2d::Label* label1440x900;
	cocos2d::Label* label1600x900;
	cocos2d::Label* label1600x1024;
	cocos2d::Label* label1920x1080;
	cocos2d::Label* label2560x1440;
	cocos2d::Label* label3840x2160;

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
	static const std::string StringKeyMenuOptions;
	static const std::string StringKeyFullScreen;
	static const std::string StringKeyReturn;
	static const int ResolutionGroupId;
};

