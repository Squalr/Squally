#include "VideoTab.h"

#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCDirector.h"

#include "Engine/Config/ConfigManager.h"
#include "Engine/Input/ClickableNode.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Engine/UI/Controls/Checkbox.h"
#include "Engine/UI/Controls/RadioButton.h"
#include "Engine/Utils/GameUtils.h"

#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const int VideoTab::ResolutionGroupId = 299267945; // RNG based to avoid conflicts
const int VideoTab::GraphicsGroupId = 712968357; // RNG based to avoid conflicts

VideoTab* VideoTab::create()
{
	VideoTab* instance = new VideoTab();

	instance->autorelease();

	return instance;
}

VideoTab::VideoTab()
{
	this->fullScreenLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::P, Strings::Menus_Options_FullScreen::create());

	this->fullScreenLabel->setAnchorPoint(Vec2(0.0f, 0.5f));
	this->fullScreenLabel->setAlignment(TextHAlignment::LEFT);
	this->fullScreenLabel->enableOutline(Color4B::BLACK, 2);

	ClickableNode* uncheckedClickableNode = ClickableNode::create(UIResources::Menus_OptionsMenu_ToggleButtonOff, UIResources::Menus_OptionsMenu_ToggleButtonOffHover);
	ClickableNode* checkedClickableNode = ClickableNode::create(UIResources::Menus_OptionsMenu_ToggleButtonOn, UIResources::Menus_OptionsMenu_ToggleButtonOnHover);
	this->fullScreenButton = Checkbox::create(uncheckedClickableNode, checkedClickableNode, ConfigManager::getIsFullScreen(), CC_CALLBACK_2(VideoTab::onFullScreenChanged, this));

	this->label1080x768 = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::Small, Strings::Menus_Options_Resolution1080x768::create());
	this->label1152x864 = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::Small, Strings::Menus_Options_Resolution1152x864::create());
	this->label1280x720 = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::Small, Strings::Menus_Options_Resolution1280x720::create());
	this->label1280x960 = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::Small, Strings::Menus_Options_Resolution1280x960::create());
	this->label1280x1024 = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::Small, Strings::Menus_Options_Resolution1280x1024::create());
	this->label1440x900 = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::Small, Strings::Menus_Options_Resolution1440x900::create());
	this->label1600x900 = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::Small, Strings::Menus_Options_Resolution1600x900::create());
	this->label1600x1024 = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::Small, Strings::Menus_Options_Resolution1600x1024::create());
	this->label1920x1080 = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::Small, Strings::Menus_Options_Resolution1920x1080::create());
	this->label2560x1440 = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::Small, Strings::Menus_Options_Resolution2560x1440::create());
	this->label3840x2160 = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::Small, Strings::Menus_Options_Resolution3840x2160::create());

	this->option1080x768 = RadioButton::create(
		ClickableNode::create(UIResources::Menus_OptionsMenu_RadioButtonSelected, UIResources::Menus_OptionsMenu_RadioButtonSelectedHover),
		ClickableNode::create(UIResources::Menus_OptionsMenu_RadioButtonEmpty, UIResources::Menus_OptionsMenu_RadioButtonHover),
	 	VideoTab::ResolutionGroupId
	);
	this->option1152x864 = RadioButton::create(
		ClickableNode::create(UIResources::Menus_OptionsMenu_RadioButtonSelected, UIResources::Menus_OptionsMenu_RadioButtonSelectedHover),
		ClickableNode::create(UIResources::Menus_OptionsMenu_RadioButtonEmpty, UIResources::Menus_OptionsMenu_RadioButtonHover),
	 	VideoTab::ResolutionGroupId
	);
	this->option1280x720 = RadioButton::create(
		ClickableNode::create(UIResources::Menus_OptionsMenu_RadioButtonSelected, UIResources::Menus_OptionsMenu_RadioButtonSelectedHover),
		ClickableNode::create(UIResources::Menus_OptionsMenu_RadioButtonEmpty, UIResources::Menus_OptionsMenu_RadioButtonHover),
	 	VideoTab::ResolutionGroupId
	);
	this->option1280x960 = RadioButton::create(
		ClickableNode::create(UIResources::Menus_OptionsMenu_RadioButtonSelected, UIResources::Menus_OptionsMenu_RadioButtonSelectedHover),
		ClickableNode::create(UIResources::Menus_OptionsMenu_RadioButtonEmpty, UIResources::Menus_OptionsMenu_RadioButtonHover),
	 	VideoTab::ResolutionGroupId
	);
	this->option1280x1024 = RadioButton::create(
		ClickableNode::create(UIResources::Menus_OptionsMenu_RadioButtonSelected, UIResources::Menus_OptionsMenu_RadioButtonSelectedHover),
		ClickableNode::create(UIResources::Menus_OptionsMenu_RadioButtonEmpty, UIResources::Menus_OptionsMenu_RadioButtonHover),
	 	VideoTab::ResolutionGroupId
	);
	this->option1440x900 = RadioButton::create(
		ClickableNode::create(UIResources::Menus_OptionsMenu_RadioButtonSelected, UIResources::Menus_OptionsMenu_RadioButtonSelectedHover),
		ClickableNode::create(UIResources::Menus_OptionsMenu_RadioButtonEmpty, UIResources::Menus_OptionsMenu_RadioButtonHover),
	 	VideoTab::ResolutionGroupId
	);
	this->option1600x900 = RadioButton::create(
		ClickableNode::create(UIResources::Menus_OptionsMenu_RadioButtonSelected, UIResources::Menus_OptionsMenu_RadioButtonSelectedHover),
		ClickableNode::create(UIResources::Menus_OptionsMenu_RadioButtonEmpty, UIResources::Menus_OptionsMenu_RadioButtonHover),
	 	VideoTab::ResolutionGroupId
	);
	this->option1600x1024 = RadioButton::create(
		ClickableNode::create(UIResources::Menus_OptionsMenu_RadioButtonSelected, UIResources::Menus_OptionsMenu_RadioButtonSelectedHover),
		ClickableNode::create(UIResources::Menus_OptionsMenu_RadioButtonEmpty, UIResources::Menus_OptionsMenu_RadioButtonHover),
	 	VideoTab::ResolutionGroupId
	);
	this->option1920x1080 = RadioButton::create(
		ClickableNode::create(UIResources::Menus_OptionsMenu_RadioButtonSelected, UIResources::Menus_OptionsMenu_RadioButtonSelectedHover),
		ClickableNode::create(UIResources::Menus_OptionsMenu_RadioButtonEmpty, UIResources::Menus_OptionsMenu_RadioButtonHover),
	 	VideoTab::ResolutionGroupId
	);
	this->option2560x1440 = RadioButton::create(
		ClickableNode::create(UIResources::Menus_OptionsMenu_RadioButtonSelected, UIResources::Menus_OptionsMenu_RadioButtonSelectedHover),
		ClickableNode::create(UIResources::Menus_OptionsMenu_RadioButtonEmpty, UIResources::Menus_OptionsMenu_RadioButtonHover),
	 	VideoTab::ResolutionGroupId
	);
	this->option3840x2160 = RadioButton::create(
		ClickableNode::create(UIResources::Menus_OptionsMenu_RadioButtonSelected, UIResources::Menus_OptionsMenu_RadioButtonSelectedHover),
		ClickableNode::create(UIResources::Menus_OptionsMenu_RadioButtonEmpty, UIResources::Menus_OptionsMenu_RadioButtonHover),
	 	VideoTab::ResolutionGroupId
	);

	this->graphicEffectsLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::P, Strings::Menus_Options_GraphicEffects::create());
	this->highQualityLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::Small, Strings::Menus_Options_HighQuality::create());
	this->lowQualityLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::Small, Strings::Menus_Options_LowQuality::create());

	this->optionLowQuality = RadioButton::create(
		ClickableNode::create(UIResources::Menus_OptionsMenu_RadioButtonSelected, UIResources::Menus_OptionsMenu_RadioButtonSelectedHover),
		ClickableNode::create(UIResources::Menus_OptionsMenu_RadioButtonEmpty, UIResources::Menus_OptionsMenu_RadioButtonHover),
	 	VideoTab::GraphicsGroupId
	);
	this->optionHighQuality = RadioButton::create(
		ClickableNode::create(UIResources::Menus_OptionsMenu_RadioButtonSelected, UIResources::Menus_OptionsMenu_RadioButtonSelectedHover),
		ClickableNode::create(UIResources::Menus_OptionsMenu_RadioButtonEmpty, UIResources::Menus_OptionsMenu_RadioButtonHover),
	 	VideoTab::GraphicsGroupId
	);

	Size shadowSize = Size(-2.0f, -2.0f);
	int shadowBlur = 2;
	Color3B textColor = Color3B::WHITE;
	Color4B shadowColor = Color4B::BLACK;
	Color3B highlightColor = Color3B::YELLOW;
	Color4B glowColor = Color4B::ORANGE;

	LocalizedLabel*	returnLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::P, Strings::Menus_Return::create());
	LocalizedLabel*	returnLabelHover = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::P, Strings::Menus_Return::create());

	returnLabel->setColor(textColor);
	returnLabel->enableShadow(shadowColor, shadowSize, shadowBlur);
	returnLabel->enableGlow(shadowColor);

	returnLabelHover->setColor(highlightColor);
	returnLabelHover->enableShadow(shadowColor, shadowSize, shadowBlur);
	returnLabelHover->enableGlow(glowColor);
	
	this->label1080x768->enableOutline(Color4B::BLACK, 2);
	this->label1152x864->enableOutline(Color4B::BLACK, 2);
	this->label1280x720->enableOutline(Color4B::BLACK, 2);
	this->label1280x960->enableOutline(Color4B::BLACK, 2);
	this->label1280x1024->enableOutline(Color4B::BLACK, 2);
	this->label1440x900->enableOutline(Color4B::BLACK, 2);
	this->label1600x900->enableOutline(Color4B::BLACK, 2);
	this->label1600x1024->enableOutline(Color4B::BLACK, 2);
	this->label1920x1080->enableOutline(Color4B::BLACK, 2);
	this->label2560x1440->enableOutline(Color4B::BLACK, 2);
	this->label3840x2160->enableOutline(Color4B::BLACK, 2);

	this->graphicEffectsLabel->enableOutline(Color4B::BLACK, 2);
	this->highQualityLabel->enableOutline(Color4B::BLACK, 2);
	this->lowQualityLabel->enableOutline(Color4B::BLACK, 2);

	this->highQualityLabel->setAnchorPoint(Vec2(0.0f, 0.5f));
	this->lowQualityLabel->setAnchorPoint(Vec2(0.0f, 0.5f));

	this->option1080x768->setCheckCallback(CC_CALLBACK_1(VideoTab::onResolutionChanged, this));
	this->option1152x864->setCheckCallback(CC_CALLBACK_1(VideoTab::onResolutionChanged, this));
	this->option1600x1024->setCheckCallback(CC_CALLBACK_1(VideoTab::onResolutionChanged, this));
	this->option1280x720->setCheckCallback(CC_CALLBACK_1(VideoTab::onResolutionChanged, this));
	this->option1280x960->setCheckCallback(CC_CALLBACK_1(VideoTab::onResolutionChanged, this));
	this->option1280x1024->setCheckCallback(CC_CALLBACK_1(VideoTab::onResolutionChanged, this));
	this->option1440x900->setCheckCallback(CC_CALLBACK_1(VideoTab::onResolutionChanged, this));
	this->option1600x900->setCheckCallback(CC_CALLBACK_1(VideoTab::onResolutionChanged, this));
	this->option1600x1024->setCheckCallback(CC_CALLBACK_1(VideoTab::onResolutionChanged, this));
	this->option1920x1080->setCheckCallback(CC_CALLBACK_1(VideoTab::onResolutionChanged, this));
	this->option2560x1440->setCheckCallback(CC_CALLBACK_1(VideoTab::onResolutionChanged, this));
	this->option3840x2160->setCheckCallback(CC_CALLBACK_1(VideoTab::onResolutionChanged, this));

	this->optionLowQuality->setCheckCallback(CC_CALLBACK_1(VideoTab::onGraphicsChanged, this));
	this->optionHighQuality->setCheckCallback(CC_CALLBACK_1(VideoTab::onGraphicsChanged, this));

	this->addChild(this->fullScreenLabel);
	this->addChild(this->fullScreenButton);

	this->addChild(this->label1080x768);
	this->addChild(this->label1152x864);
	this->addChild(this->label1280x720);
	this->addChild(this->label1280x960);
	this->addChild(this->label1280x1024);
	this->addChild(this->label1440x900);
	this->addChild(this->label1600x900);
	this->addChild(this->label1600x1024);
	this->addChild(this->label1920x1080);
	this->addChild(this->label2560x1440);
	this->addChild(this->label3840x2160);

	this->addChild(this->option1080x768);
	this->addChild(this->option1152x864);
	this->addChild(this->option1280x720);
	this->addChild(this->option1280x960);
	this->addChild(this->option1280x1024);
	this->addChild(this->option1440x900);
	this->addChild(this->option1600x900);
	this->addChild(this->option1600x1024);
	this->addChild(this->option1920x1080);
	this->addChild(this->option2560x1440);
	this->addChild(this->option3840x2160);

	this->addChild(this->graphicEffectsLabel);
	this->addChild(this->lowQualityLabel);
	this->addChild(this->highQualityLabel);

	this->addChild(this->optionHighQuality);
	this->addChild(this->optionLowQuality);

	switch (ConfigManager::getResolution())
	{
		case ConfigManager::ResolutionSetting::R1080x768:
		{
			this->option1080x768->check(false);
			break;
		}
		case ConfigManager::ResolutionSetting::R1152x864:
		{
			this->option1152x864->check(false);
			break;
		}
		case ConfigManager::ResolutionSetting::R1280x720:
		{
			this->option1280x720->check(false);
			break;
		}
		case ConfigManager::ResolutionSetting::R1280x960:
		{
			this->option1280x960->check(false);
			break;
		}
		case ConfigManager::ResolutionSetting::R1280x1024:
		{
			this->option1280x1024->check(false);
			break;
		}
		case ConfigManager::ResolutionSetting::R1440x900:
		{
			this->option1440x900->check(false);
			break;
		}
		case ConfigManager::ResolutionSetting::R1600x900:
		{
			this->option1600x900->check(false);
			break;
		}
		case ConfigManager::ResolutionSetting::R1600x1024:
		{
			this->option1600x1024->check(false);
			break;
		}
		case ConfigManager::ResolutionSetting::R1920x1080:
		{
			this->option1920x1080->check(false);
			break;
		}
		case ConfigManager::ResolutionSetting::R2560x1440:
		{
			this->option2560x1440->check(false);
			break;
		}
		case ConfigManager::ResolutionSetting::R3840x2160:
		default:
		{
			this->option3840x2160->check(false);
			break;
		}
	}
	 
	switch (ConfigManager::getGraphics())
	{
		case ConfigManager::GraphicsSetting::FastLowQuality:
		{
			this->optionLowQuality->check(false);
			break;
		}
		case ConfigManager::GraphicsSetting::SlowHighQuality:
		default:
		{
			this->optionHighQuality->check(false);
			break;
		}
	}

	if (ConfigManager::getIsFullScreen())
	{
		this->hideResolutionOptions();
	}
	else
	{
		this->showResolutionOptions();
	}
}

VideoTab::~VideoTab()
{
}

void VideoTab::onEnter()
{
	super::onEnter();

	float delay = 0.1f;
	float duration = 0.25f;

	GameUtils::fadeInObject(this->fullScreenLabel, delay, duration);
	GameUtils::fadeInObject(this->fullScreenButton, delay, duration);

	GameUtils::fadeInObject(this->label1080x768, delay, duration);
	GameUtils::fadeInObject(this->label1152x864, delay, duration);
	GameUtils::fadeInObject(this->label1280x720, delay, duration);
	GameUtils::fadeInObject(this->label1280x960, delay, duration);
	GameUtils::fadeInObject(this->label1280x1024, delay, duration);
	GameUtils::fadeInObject(this->label1440x900, delay, duration);
	GameUtils::fadeInObject(this->label1600x900, delay, duration);
	GameUtils::fadeInObject(this->label1600x1024, delay, duration);
	GameUtils::fadeInObject(this->label1920x1080, delay, duration);

	GameUtils::fadeInObject(this->option1080x768, delay, duration);
	GameUtils::fadeInObject(this->option1152x864, delay, duration);
	GameUtils::fadeInObject(this->option1280x720, delay, duration);
	GameUtils::fadeInObject(this->option1280x960, delay, duration);
	GameUtils::fadeInObject(this->option1280x1024, delay, duration);
	GameUtils::fadeInObject(this->option1440x900, delay, duration);
	GameUtils::fadeInObject(this->option1600x900, delay, duration);
	GameUtils::fadeInObject(this->option1600x1024, delay, duration);
	GameUtils::fadeInObject(this->option1920x1080, delay, duration);
	GameUtils::fadeInObject(this->option2560x1440, delay, duration);
	GameUtils::fadeInObject(this->option3840x2160, delay, duration);
}

void VideoTab::initializeListeners()
{
	super::initializeListeners();
}

void VideoTab::initializePositions()
{
	super::initializePositions();

	this->fullScreenButton->setPosition(Vec2(-292.0f, 196.0f));
	this->fullScreenLabel->setPosition(Vec2(-208.0f, 196.0f));

	const float spacing = 160.0f;
	const float base = -320.0f;
	const float baseY = 128.0f;
	const float offsetY = 48.0f;
	const float textOffset = 70.0f;

	this->label1080x768->setPosition(Vec2(base + spacing * 0.0f, baseY));
	this->label1152x864->setPosition(Vec2(base + spacing * 1.0f, baseY));
	this->label1280x720->setPosition(Vec2(base + spacing * 2.0f, baseY));
	this->label1280x960->setPosition(Vec2(base + spacing * 3.0f, baseY));
	this->option1080x768->setPosition(Vec2((base + textOffset) + spacing * 0.0f, baseY));
	this->option1152x864->setPosition(Vec2((base + textOffset) + spacing * 1.0f, baseY));
	this->option1280x720->setPosition(Vec2((base + textOffset) + spacing * 2.0f, baseY));
	this->option1280x960->setPosition(Vec2((base + textOffset) + spacing * 3.0f, baseY));

	this->label1280x1024->setPosition(Vec2(base + spacing * 0.0f, baseY - offsetY));
	this->label1440x900->setPosition(Vec2(base + spacing * 1.0f, baseY - offsetY));
	this->label1600x900->setPosition(Vec2(base + spacing * 2.0f, baseY - offsetY));
	this->label1600x1024->setPosition(Vec2(base + spacing * 3.0f, baseY - offsetY));
	this->option1280x1024->setPosition(Vec2((base + textOffset) + spacing * 0.0f, baseY - offsetY));
	this->option1440x900->setPosition(Vec2((base + textOffset) + spacing * 1.0f, baseY - offsetY));
	this->option1600x900->setPosition(Vec2((base + textOffset) + spacing * 2.0f, baseY - offsetY));
	this->option1600x1024->setPosition(Vec2((base + textOffset) + spacing * 3.0f, baseY - offsetY));

	this->label1920x1080->setPosition(Vec2(base + spacing * 0.0f, baseY - offsetY * 2.0f));
	this->label2560x1440->setPosition(Vec2(base + spacing * 1.0f, baseY - offsetY * 2.0f));
	this->label3840x2160->setPosition(Vec2(base + spacing * 2.0f, baseY - offsetY * 2.0f));
	this->option1920x1080->setPosition(Vec2((base + textOffset) + spacing * 0.0f, baseY - offsetY * 2.0f));
	this->option2560x1440->setPosition(Vec2((base + textOffset) + spacing * 1.0f, baseY - offsetY * 2.0f));
	this->option3840x2160->setPosition(Vec2((base + textOffset) + spacing * 2.0f, baseY - offsetY * 2.0f));
	
	this->graphicEffectsLabel->setPosition(Vec2(base + 32.0f, baseY - 160.0f));
	this->optionHighQuality->setPosition(Vec2(base, baseY - 160.0f - offsetY * 1.0f));
	this->optionLowQuality->setPosition(Vec2(base, baseY - 160.0f - offsetY * 2.0f));
	this->highQualityLabel->setPosition(Vec2(base + 32.0f, baseY - 160.0f - offsetY * 1.0f));
	this->lowQualityLabel->setPosition(Vec2(base + 32.0f, baseY - 160.0f - offsetY * 2.0f));
}

bool VideoTab::onFullScreenChanged(Checkbox* checkbox, bool isFullScreen)
{
	ConfigManager::setIsFullScreen(isFullScreen);

	if (isFullScreen)
	{
		this->hideResolutionOptions();
	}
	else
	{
		this->showResolutionOptions();
	}

	return isFullScreen;
}

void VideoTab::onResolutionChanged(RadioButton* radioButton)
{
	if (radioButton == this->option1080x768)
	{
		ConfigManager::setResolution(ConfigManager::ResolutionSetting::R1080x768);
	}
	else if (radioButton == this->option1152x864)
	{
		ConfigManager::setResolution(ConfigManager::ResolutionSetting::R1152x864);
	}
	else if (radioButton == this->option1280x720)
	{
		ConfigManager::setResolution(ConfigManager::ResolutionSetting::R1280x720);
	}
	else if (radioButton == this->option1280x960)
	{
		ConfigManager::setResolution(ConfigManager::ResolutionSetting::R1280x960);
	}
	else if (radioButton == this->option1280x1024)
	{
		ConfigManager::setResolution(ConfigManager::ResolutionSetting::R1280x1024);
	}
	else if (radioButton == this->option1440x900)
	{
		ConfigManager::setResolution(ConfigManager::ResolutionSetting::R1440x900);
	}
	else if (radioButton == this->option1600x900)
	{
		ConfigManager::setResolution(ConfigManager::ResolutionSetting::R1600x900);
	}
	else if (radioButton == this->option1600x1024)
	{
		ConfigManager::setResolution(ConfigManager::ResolutionSetting::R1600x1024);
	}
	else if (radioButton == this->option1920x1080)
	{
		ConfigManager::setResolution(ConfigManager::ResolutionSetting::R1920x1080);
	}
	else if (radioButton == this->option2560x1440)
	{
		ConfigManager::setResolution(ConfigManager::ResolutionSetting::R2560x1440);
	}
	else if (radioButton == this->option3840x2160)
	{
		ConfigManager::setResolution(ConfigManager::ResolutionSetting::R3840x2160);
	}
}

void VideoTab::onGraphicsChanged(RadioButton* radioButton)
{
	if (radioButton == this->optionLowQuality)
	{
		ConfigManager::setGraphics(ConfigManager::GraphicsSetting::FastLowQuality);
	}
	else if (radioButton == this->optionHighQuality)
	{
		ConfigManager::setGraphics(ConfigManager::GraphicsSetting::SlowHighQuality);
	}
}

void VideoTab::showResolutionOptions()
{
	this->label1080x768->setVisible(true);
	this->label1152x864->setVisible(true);
	this->label1280x720->setVisible(true);
	this->label1280x960->setVisible(true);
	this->label1280x1024->setVisible(true);
	this->label1440x900->setVisible(true);
	this->label1600x900->setVisible(true);
	this->label1600x1024->setVisible(true);
	this->label1920x1080->setVisible(true);
	this->label2560x1440->setVisible(true);
	this->label3840x2160->setVisible(true);

	this->option1080x768->setVisible(true);
	this->option1152x864->setVisible(true);
	this->option1600x1024->setVisible(true);
	this->option1280x720->setVisible(true);
	this->option1280x960->setVisible(true);
	this->option1280x1024->setVisible(true);
	this->option1440x900->setVisible(true);
	this->option1600x900->setVisible(true);
	this->option1600x1024->setVisible(true);
	this->option1920x1080->setVisible(true);
	this->option2560x1440->setVisible(true);
	this->option3840x2160->setVisible(true);
}

void VideoTab::hideResolutionOptions()
{
	this->label1080x768->setVisible(false);
	this->label1152x864->setVisible(false);
	this->label1280x720->setVisible(false);
	this->label1280x960->setVisible(false);
	this->label1280x1024->setVisible(false);
	this->label1440x900->setVisible(false);
	this->label1600x900->setVisible(false);
	this->label1600x1024->setVisible(false);
	this->label1920x1080->setVisible(false);
	this->label2560x1440->setVisible(false);
	this->label3840x2160->setVisible(false);

	this->option1080x768->setVisible(false);
	this->option1152x864->setVisible(false);
	this->option1280x720->setVisible(false);
	this->option1280x960->setVisible(false);
	this->option1280x1024->setVisible(false);
	this->option1440x900->setVisible(false);
	this->option1600x900->setVisible(false);
	this->option1600x1024->setVisible(false);
	this->option1920x1080->setVisible(false);
	this->option2560x1440->setVisible(false);
	this->option3840x2160->setVisible(false);
}
