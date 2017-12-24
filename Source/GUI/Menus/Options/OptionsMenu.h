#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "Resources.h"
#include "Config/SoundManager.h"
#include "Config/ConfigManager.h"
#include "GUI/Components/FadeScene.h"
#include "GUI/Components/Mouse.h"
#include "GUI/Components/MenuLabel.h"
#include "GUI/Components/MenuSprite.h"
#include "GUI/Components/Slider.h"
#include "GUI/Components/RadioButton.h"
#include "GUI/Components/ToggleButton.h"
#include "GUI/Menus/MenuBackground.h"

using namespace cocos2d;

class OptionsMenu : public FadeScene
{
public:
	static OptionsMenu * create();

protected:
	OptionsMenu();
	~OptionsMenu();

private:
	void onEnter() override;
	void OnSoundVolumeUpdate(float soundVolume);
	void OnMusicVolumeUpdate(float musicVolume);
	void OnFullScreenChanged(bool isFullScreen);
	void OnResolutionChanged(RadioButton* radioButton);
	void OnCloseClick(MenuSprite* menuSprite);
	void OnKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
	void InitializeListeners();
	void InitializePositions();

	void ShowResolutionOptions();
	void HideResolutionOptions();

	Node* background;
	Sprite* optionsWindow;
	MenuSprite* closeButton;

	Sprite* musicIcon;
	Sprite* soundIcon;
	Slider* musicSlider;
	Slider* soundSlider;
	MenuLabel* fullScreenLabel;
	ToggleButton* fullScreenButton;
	MenuSprite* exitButton;

	Label* label1080x768;
	Label* label1152x864;
	Label* label1280x720;
	Label* label1280x960;
	Label* label1280x1024;
	Label* label1440x900;
	Label* label1600x900;
	Label* label1600x1024;
	Label* label1920x1080;

	RadioButton* option1080x768;
	RadioButton* option1152x864;
	RadioButton* option1280x720;
	RadioButton* option1280x960;
	RadioButton* option1280x1024;
	RadioButton* option1440x900;
	RadioButton* option1600x900;
	RadioButton* option1600x1024;
	RadioButton* option1920x1080;

	const int resolutionGroupId = 420;

	const float titleFontSize = 48.0f;
	const float menuFontSize = 32.0f;
	const float menuOffset = 0.0f;
	const float spacing = -64.0f;
};

