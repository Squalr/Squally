#include "VideoTab.h"

#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCDirector.h"

#include "Engine/Config/ConfigManager.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Engine/UI/Controls/CCheckbox.h"
#include "Engine/UI/Controls/CRadioButton.h"
#include "Engine/UI/Controls/MenuSprite.h"
#include "Engine/Utils/GameUtils.h"

#include "Resources/UIResources.h"

#include "Strings/Menus/Options/FullScreen.h"
#include "Strings/Menus/Options/Resolution1080x768.h"
#include "Strings/Menus/Options/Resolution1152x864.h"
#include "Strings/Menus/Options/Resolution1280x720.h"
#include "Strings/Menus/Options/Resolution1280x960.h"
#include "Strings/Menus/Options/Resolution1280x1024.h"
#include "Strings/Menus/Options/Resolution1440x900.h"
#include "Strings/Menus/Options/Resolution1600x900.h"
#include "Strings/Menus/Options/Resolution1600x1024.h"
#include "Strings/Menus/Options/Resolution1920x1080.h"
#include "Strings/Menus/Options/Resolution2560x1440.h"
#include "Strings/Menus/Options/Resolution3840x2160.h"
#include "Strings/Menus/Return.h"

using namespace cocos2d;

const int VideoTab::ResolutionGroupId = 420;

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

	MenuSprite* uncheckedMenuSprite = MenuSprite::create(UIResources::Menus_OptionsMenu_ToggleButtonOff, UIResources::Menus_OptionsMenu_ToggleButtonOffHover);
	MenuSprite* checkedMenuSprite = MenuSprite::create(UIResources::Menus_OptionsMenu_ToggleButtonOn, UIResources::Menus_OptionsMenu_ToggleButtonOnHover);
	this->fullScreenButton = CCheckbox::create(uncheckedMenuSprite, checkedMenuSprite, ConfigManager::getIsFullScreen(), CC_CALLBACK_2(VideoTab::onFullScreenChanged, this));

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

	this->option1080x768 = CRadioButton::create(VideoTab::ResolutionGroupId);
	this->option1152x864 = CRadioButton::create(VideoTab::ResolutionGroupId);
	this->option1280x720 = CRadioButton::create(VideoTab::ResolutionGroupId);
	this->option1280x960 = CRadioButton::create(VideoTab::ResolutionGroupId);
	this->option1280x1024 = CRadioButton::create(VideoTab::ResolutionGroupId);
	this->option1440x900 = CRadioButton::create(VideoTab::ResolutionGroupId);
	this->option1600x900 = CRadioButton::create(VideoTab::ResolutionGroupId);
	this->option1600x1024 = CRadioButton::create(VideoTab::ResolutionGroupId);
	this->option1920x1080 = CRadioButton::create(VideoTab::ResolutionGroupId);
	this->option2560x1440 = CRadioButton::create(VideoTab::ResolutionGroupId);
	this->option3840x2160 = CRadioButton::create(VideoTab::ResolutionGroupId);

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

	switch (ConfigManager::getResolution())
	{
		case ConfigManager::ResolutionSetting::R1080x768:
		{
			this->option1080x768->check();
			break;
		}
		case ConfigManager::ResolutionSetting::R1152x864:
		{
			this->option1152x864->check();
			break;
		}
		case ConfigManager::ResolutionSetting::R1280x720:
		{
			this->option1280x720->check();
			break;
		}
		case ConfigManager::ResolutionSetting::R1280x960:
		{
			this->option1280x960->check();
			break;
		}
		case ConfigManager::ResolutionSetting::R1280x1024:
		{
			this->option1280x1024->check();
			break;
		}
		case ConfigManager::ResolutionSetting::R1440x900:
		{
			this->option1440x900->check();
			break;
		}
		case ConfigManager::ResolutionSetting::R1600x900:
		{
			this->option1600x900->check();
			break;
		}
		case ConfigManager::ResolutionSetting::R1600x1024:
		{
			this->option1600x1024->check();
			break;
		}
		case ConfigManager::ResolutionSetting::R1920x1080:
		{
			this->option1920x1080->check();
			break;
		}
		case ConfigManager::ResolutionSetting::R2560x1440:
		{
			this->option2560x1440->check();
			break;
		}
		case ConfigManager::ResolutionSetting::R3840x2160:
		default:
		{
			this->option3840x2160->check();
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

	this->label1080x768->setPosition(Vec2(base + spacing * 0, baseY));
	this->label1152x864->setPosition(Vec2(base + spacing * 1, baseY));
	this->label1280x720->setPosition(Vec2(base + spacing * 2, baseY));
	this->label1280x960->setPosition(Vec2(base + spacing * 3, baseY));
	this->option1080x768->setPosition(Vec2((base + textOffset) + spacing * 0, baseY));
	this->option1152x864->setPosition(Vec2((base + textOffset) + spacing * 1, baseY));
	this->option1280x720->setPosition(Vec2((base + textOffset) + spacing * 2, baseY));
	this->option1280x960->setPosition(Vec2((base + textOffset) + spacing * 3, baseY));

	this->label1280x1024->setPosition(Vec2(base + spacing * 0, baseY - offsetY));
	this->label1440x900->setPosition(Vec2(base + spacing * 1, baseY - offsetY));
	this->label1600x900->setPosition(Vec2(base + spacing * 2, baseY - offsetY));
	this->label1600x1024->setPosition(Vec2(base + spacing * 3, baseY - offsetY));
	this->option1280x1024->setPosition(Vec2((base + textOffset) + spacing * 0, baseY - offsetY));
	this->option1440x900->setPosition(Vec2((base + textOffset) + spacing * 1, baseY - offsetY));
	this->option1600x900->setPosition(Vec2((base + textOffset) + spacing * 2, baseY - offsetY));
	this->option1600x1024->setPosition(Vec2((base + textOffset) + spacing * 3, baseY - offsetY));

	this->label1920x1080->setPosition(Vec2(base + spacing * 0, baseY - offsetY * 2));
	this->label2560x1440->setPosition(Vec2(base + spacing * 1, baseY - offsetY * 2));
	this->label3840x2160->setPosition(Vec2(base + spacing * 2, baseY - offsetY * 2));
	this->option1920x1080->setPosition(Vec2((base + textOffset) + spacing * 0, baseY - offsetY * 2));
	this->option2560x1440->setPosition(Vec2((base + textOffset) + spacing * 1, baseY - offsetY * 2));
	this->option3840x2160->setPosition(Vec2((base + textOffset) + spacing * 2, baseY - offsetY * 2));
}

bool VideoTab::onFullScreenChanged(CCheckbox* checkbox, bool isFullScreen)
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

void VideoTab::onResolutionChanged(CRadioButton* radioButton)
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
