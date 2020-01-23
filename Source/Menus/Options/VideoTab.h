#pragma once
#include <functional>

#include "Engine/UI/HUD/Hud.h"

class Checkbox;
class ClickableNode;
class ClickableTextNode;
class LocalizedLabel;
class RadioButton;
class Slider;

class VideoTab : public SmartNode
{
public:
	static VideoTab* create();

	void setBackClickCallback(std::function<void()> backClickCallback);

protected:
	VideoTab();
	virtual ~VideoTab();

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
	bool onFullScreenChanged(Checkbox* checkbox, bool isFullScreen);
	void onResolutionChanged(RadioButton* radioButton);
	void onGraphicsChanged(RadioButton* radioButton);
	void showResolutionOptions();
	void hideResolutionOptions();

	LocalizedLabel* fullScreenLabel;
	Checkbox* fullScreenButton;

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

	RadioButton* option1080x768;
	RadioButton* option1152x864;
	RadioButton* option1280x720;
	RadioButton* option1280x960;
	RadioButton* option1280x1024;
	RadioButton* option1440x900;
	RadioButton* option1600x900;
	RadioButton* option1600x1024;
	RadioButton* option1920x1080;
	RadioButton* option2560x1440;
	RadioButton* option3840x2160;

	LocalizedLabel* graphicEffectsLabel;
	LocalizedLabel* highQualityLabel;
	LocalizedLabel* lowQualityLabel;

	RadioButton* optionLowQuality;
	RadioButton* optionHighQuality;

	static const int ResolutionGroupId;
	static const int GraphicsGroupId;
};
