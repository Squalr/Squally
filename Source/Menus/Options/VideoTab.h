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

class VideoTab : public SmartNode
{
public:
	static VideoTab* create();

	void setBackClickCallback(std::function<void()> backClickCallback);

protected:
	VideoTab();
	~VideoTab();

private:
	typedef SmartNode super;

	enum class Tabs
	{
		General,
		Video,
	};

	void onEnter() override;
	void initializeListeners() override;
	void initializePositions() override;
	bool onFullScreenChanged(CCheckbox* checkbox, bool isFullScreen);
	void onResolutionChanged(CRadioButton* radioButton);
	void showResolutionOptions();
	void hideResolutionOptions();

	LocalizedLabel* fullScreenLabel;
	CCheckbox* fullScreenButton;

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

	static const int ResolutionGroupId;
};
