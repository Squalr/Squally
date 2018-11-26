#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"

#include "Engine/Config/ConfigManager.h"
#include "Engine/Localization/Localization.h"
#include "Engine/SmartNode.h"
#include "Engine/Sound/SoundManager.h"
#include "Events/NavigationEvents.h"
#include "Engine/UI/Controls/CCheckbox.h"
#include "Engine/UI/Controls/CRadioButton.h"
#include "Engine/UI/Controls/CSlider.h"
#include "Engine/UI/Controls/MenuSprite.h"
#include "Engine/UI/FadeScene.h"
#include "Engine/UI/Controls/TextMenuSprite.h"
#include "Engine/UI/Mouse.h"

using namespace cocos2d;

class OptionsMenu : public SmartNode
{
public:
	static OptionsMenu * create();

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
	void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
	void showResolutionOptions();
	void hideResolutionOptions();
	void onExit();

	std::function<void()> backClickCallback;

	Node* background;
	Sprite* optionsWindow;
	Label* titleLabel;
	MenuSprite* closeButton;

	Sprite* musicIcon;
	Sprite* soundIcon;
	CSlider* musicSlider;
	CSlider* soundSlider;
	Label* fullScreenLabel;
	CCheckbox* fullScreenButton;
	TextMenuSprite* returnButton;

	Label* label1080x768;
	Label* label1152x864;
	Label* label1280x720;
	Label* label1280x960;
	Label* label1280x1024;
	Label* label1440x900;
	Label* label1600x900;
	Label* label1600x1024;
	Label* label1920x1080;
	Label* label2560x1440;
	Label* label3840x2160;

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

	static const Color3B TitleColor;
	static const std::string StringKeyMenuOptions;
	static const std::string StringKeyFullScreen;
	static const std::string StringKeyReturn;
	static const int ResolutionGroupId;
};

