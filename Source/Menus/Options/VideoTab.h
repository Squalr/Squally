#pragma once
#include <functional>

#include "Engine/SmartNode.h"

class Checkbox;
class LocalizedLabel;
class RadioButton;

class VideoTab : public SmartNode
{
public:
	static VideoTab* create();

	void setBackClickCallback(std::function<void()> backClickCallback);

protected:
	VideoTab();
	virtual ~VideoTab();
	
	void onEnter() override;
	void initializeListeners() override;
	void initializePositions() override;

private:
	typedef SmartNode super;

	enum class Tabs
	{
		General,
		Video,
	};

	bool onFullScreenChanged(Checkbox* checkbox, bool isFullScreen);
	void onResolutionChanged(RadioButton* radioButton);
	void onGraphicsChanged(RadioButton* radioButton);
	void showResolutionOptions();
	void hideResolutionOptions();

	LocalizedLabel* fullScreenLabel = nullptr;
	Checkbox* fullScreenButton = nullptr;

	LocalizedLabel* label1080x768 = nullptr;
	LocalizedLabel* label1152x864 = nullptr;
	LocalizedLabel* label1280x720 = nullptr;
	LocalizedLabel* label1280x960 = nullptr;
	LocalizedLabel* label1280x1024 = nullptr;
	LocalizedLabel* label1440x900 = nullptr;
	LocalizedLabel* label1600x900 = nullptr;
	LocalizedLabel* label1600x1024 = nullptr;
	LocalizedLabel* label1920x1080 = nullptr;
	LocalizedLabel* label2560x1440 = nullptr;
	LocalizedLabel* label3840x2160 = nullptr;

	RadioButton* option1080x768 = nullptr;
	RadioButton* option1152x864 = nullptr;
	RadioButton* option1280x720 = nullptr;
	RadioButton* option1280x960 = nullptr;
	RadioButton* option1280x1024 = nullptr;
	RadioButton* option1440x900 = nullptr;
	RadioButton* option1600x900 = nullptr;
	RadioButton* option1600x1024 = nullptr;
	RadioButton* option1920x1080 = nullptr;
	RadioButton* option2560x1440 = nullptr;
	RadioButton* option3840x2160 = nullptr;

	LocalizedLabel* graphicEffectsLabel = nullptr;
	LocalizedLabel* highQualityLabel = nullptr;
	LocalizedLabel* lowQualityLabel = nullptr;

	RadioButton* optionLowQuality = nullptr;
	RadioButton* optionHighQuality = nullptr;

	static const int ResolutionGroupId;
	static const int GraphicsGroupId;
};
