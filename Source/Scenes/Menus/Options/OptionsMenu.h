#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"

#include "Config/ConfigManager.h"
#include "Engine/Sound/SoundManager.h"
#include "Events/NavigationEvents.h"
#include "Engine/Rendering/Components/CCheckbox.h"
#include "Engine/Rendering/Components/CRadioButton.h"
#include "Engine/Rendering/Components/CSlider.h"
#include "Engine/Rendering/Components/FadeScene.h"
#include "Engine/Rendering/Components/MenuSprite.h"
#include "Engine/Rendering/Components/Mouse.h"
#include "Resources.h"
#include "Scenes/Menus/MenuBackground.h"

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
	void onSoundVolumeUpdate(float soundVolume);
	void onMusicVolumeUpdate(float musicVolume);
	bool onFullScreenChanged(CCheckbox* checkbox, bool isFullScreen);
	void onResolutionChanged(CRadioButton* radioButton);
	void onCloseClick(MenuSprite* menuSprite);
	void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
	void initializeListeners();
	void initializePositions();
	void showResolutionOptions();
	void hideResolutionOptions();

	Node* background;
	Sprite* optionsWindow;
	MenuSprite* closeButton;

	Sprite* musicIcon;
	Sprite* soundIcon;
	CSlider* musicSlider;
	CSlider* soundSlider;
	Label* fullScreenLabel;
	CCheckbox* fullScreenButton;
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

	CRadioButton* option1080x768;
	CRadioButton* option1152x864;
	CRadioButton* option1280x720;
	CRadioButton* option1280x960;
	CRadioButton* option1280x1024;
	CRadioButton* option1440x900;
	CRadioButton* option1600x900;
	CRadioButton* option1600x1024;
	CRadioButton* option1920x1080;

	const int resolutionGroupId = 420;

	const float titleFontSize = 48.0f;
	const float menuFontSize = 32.0f;
	const float menuOffset = 0.0f;
	const float spacing = -64.0f;
};

