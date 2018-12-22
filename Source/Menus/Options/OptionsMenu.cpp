#include "OptionsMenu.h"

#include "cocos/2d/CCLabel.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCDirector.h"
#include "cocos/base/CCEventListenerKeyboard.h"

#include "Engine/Config/ConfigManager.h"
#include "Engine/Localization/Localization.h"
#include "Engine/Sound/SoundManager.h"
#include "Engine/UI/Controls/CCheckbox.h"
#include "Engine/UI/Controls/CRadioButton.h"
#include "Engine/UI/Controls/CSlider.h"
#include "Engine/UI/Controls/MenuSprite.h"
#include "Engine/UI/Controls/TextMenuSprite.h"
#include "Engine/UI/Mouse.h"
#include "Engine/Utils/GameUtils.h"

#include "Resources/UIResources.h"

using namespace cocos2d;

const Color3B OptionsMenu::TitleColor = Color3B(88, 188, 193);
const std::string OptionsMenu::StringKeyMenuOptions = "Menu_Options";
const std::string OptionsMenu::StringKeyFullScreen = "Menu_Options_Full_Screen";
const std::string OptionsMenu::StringKeyReturn = "Menu_Return";
const int OptionsMenu::ResolutionGroupId = 420;

OptionsMenu * OptionsMenu::create()
{
	OptionsMenu* instance = new OptionsMenu();

	instance->autorelease();

	return instance;
}

OptionsMenu::OptionsMenu()
{
	this->backClickCallback = nullptr;

	this->background = Node::create();
	this->optionsWindow = Sprite::create(UIResources::Menus_OptionsMenu_OptionsMenu);
	this->fullScreenLabel = Label::createWithTTF(Localization::resolveString(OptionsMenu::StringKeyFullScreen), Localization::getMainFont(), 24.0f);
	this->closeButton = MenuSprite::create(UIResources::Menus_Buttons_CloseButton, UIResources::Menus_Buttons_CloseButtonHover);
	this->titleLabel = Label::createWithTTF(Localization::resolveString(OptionsMenu::StringKeyMenuOptions), Localization::getMainFont(), 32.0f);

	this->titleLabel->setColor(OptionsMenu::TitleColor);
	this->titleLabel->enableShadow(Color4B::BLACK, Size(2, -2), 2);

	this->fullScreenLabel->setAlignment(TextHAlignment::LEFT);
	this->fullScreenLabel->enableOutline(Color4B::BLACK, 2.0f);

	this->musicIcon = Sprite::create(UIResources::Menus_OptionsMenu_MusicIcon);
	this->soundIcon = Sprite::create(UIResources::Menus_OptionsMenu_SoundIcon);

	this->musicSlider = CSlider::create(SoundManager::getMusicVolume());
	this->soundSlider = CSlider::create(SoundManager::getSoundVolume());

	MenuSprite* uncheckedMenuSprite = MenuSprite::create(UIResources::Menus_OptionsMenu_ToggleButtonOff, UIResources::Menus_OptionsMenu_ToggleButtonOffHover);
	MenuSprite* checkedMenuSprite = MenuSprite::create(UIResources::Menus_OptionsMenu_ToggleButtonOn, UIResources::Menus_OptionsMenu_ToggleButtonOffHover);
	this->fullScreenButton = CCheckbox::create(uncheckedMenuSprite, checkedMenuSprite, ConfigManager::getIsFullScreen(), CC_CALLBACK_2(OptionsMenu::onFullScreenChanged, this));

	this->label1080x768 = Label::createWithTTF("1080x768", Localization::getMainFont(), 14);
	this->label1152x864 = Label::createWithTTF("1152x864", Localization::getMainFont(), 14);
	this->label1280x720 = Label::createWithTTF("1280x720", Localization::getMainFont(), 14);
	this->label1280x960 = Label::createWithTTF("1280x960", Localization::getMainFont(), 14);
	this->label1280x1024 = Label::createWithTTF("1280x1024", Localization::getMainFont(), 14);
	this->label1440x900 = Label::createWithTTF("1440x900", Localization::getMainFont(), 14);
	this->label1600x900 = Label::createWithTTF("1600x900", Localization::getMainFont(), 14);
	this->label1600x1024 = Label::createWithTTF("1600x1024", Localization::getMainFont(), 14);
	this->label1920x1080 = Label::createWithTTF("1920x1080", Localization::getMainFont(), 14);
	this->label2560x1440 = Label::createWithTTF("2560x1440", Localization::getMainFont(), 14);
	this->label3840x2160 = Label::createWithTTF("3840x2160", Localization::getMainFont(), 14);

	this->option1080x768 = CRadioButton::create(OptionsMenu::ResolutionGroupId);
	this->option1152x864 = CRadioButton::create(OptionsMenu::ResolutionGroupId);
	this->option1280x720 = CRadioButton::create(OptionsMenu::ResolutionGroupId);
	this->option1280x960 = CRadioButton::create(OptionsMenu::ResolutionGroupId);
	this->option1280x1024 = CRadioButton::create(OptionsMenu::ResolutionGroupId);
	this->option1440x900 = CRadioButton::create(OptionsMenu::ResolutionGroupId);
	this->option1600x900 = CRadioButton::create(OptionsMenu::ResolutionGroupId);
	this->option1600x1024 = CRadioButton::create(OptionsMenu::ResolutionGroupId);
	this->option1920x1080 = CRadioButton::create(OptionsMenu::ResolutionGroupId);
	this->option2560x1440 = CRadioButton::create(OptionsMenu::ResolutionGroupId);
	this->option3840x2160 = CRadioButton::create(OptionsMenu::ResolutionGroupId);

	int fontSize = 24;
	Size shadowSize = Size(-2.0f, -2.0f);
	int shadowBlur = 2;
	int hoverOutlineSize = 2;
	Color3B textColor = Color3B::WHITE;
	Color4B shadowColor = Color4B::BLACK;
	Color3B highlightColor = Color3B::YELLOW;
	Color4B glowColor = Color4B::ORANGE;

	Label* returnLabel = Label::createWithTTF(Localization::resolveString(OptionsMenu::StringKeyReturn), Localization::getMainFont(), fontSize);
	Label* returnLabelHover = Label::createWithTTF(Localization::resolveString(OptionsMenu::StringKeyReturn), Localization::getMainFont(), fontSize);

	returnLabel->setColor(textColor);
	returnLabel->enableShadow(shadowColor, shadowSize, shadowBlur);
	returnLabel->enableGlow(shadowColor);

	returnLabelHover->setColor(highlightColor);
	returnLabelHover->enableShadow(shadowColor, shadowSize, shadowBlur);
	returnLabelHover->enableGlow(glowColor);

	this->returnButton = TextMenuSprite::create(
		returnLabel,
		returnLabelHover,
		UIResources::Menus_Buttons_GenericButton,
		UIResources::Menus_Buttons_GenericButtonHover);

	this->musicSlider->setProgressUpdateCallback(CC_CALLBACK_1(OptionsMenu::onMusicVolumeUpdate, this));
	this->soundSlider->setProgressUpdateCallback(CC_CALLBACK_1(OptionsMenu::onSoundVolumeUpdate, this));

	this->option1080x768->setCheckCallback(CC_CALLBACK_1(OptionsMenu::onResolutionChanged, this));
	this->option1152x864->setCheckCallback(CC_CALLBACK_1(OptionsMenu::onResolutionChanged, this));
	this->option1600x1024->setCheckCallback(CC_CALLBACK_1(OptionsMenu::onResolutionChanged, this));
	this->option1280x720->setCheckCallback(CC_CALLBACK_1(OptionsMenu::onResolutionChanged, this));
	this->option1280x960->setCheckCallback(CC_CALLBACK_1(OptionsMenu::onResolutionChanged, this));
	this->option1280x1024->setCheckCallback(CC_CALLBACK_1(OptionsMenu::onResolutionChanged, this));
	this->option1440x900->setCheckCallback(CC_CALLBACK_1(OptionsMenu::onResolutionChanged, this));
	this->option1600x900->setCheckCallback(CC_CALLBACK_1(OptionsMenu::onResolutionChanged, this));
	this->option1600x1024->setCheckCallback(CC_CALLBACK_1(OptionsMenu::onResolutionChanged, this));
	this->option1920x1080->setCheckCallback(CC_CALLBACK_1(OptionsMenu::onResolutionChanged, this));
	this->option2560x1440->setCheckCallback(CC_CALLBACK_1(OptionsMenu::onResolutionChanged, this));
	this->option3840x2160->setCheckCallback(CC_CALLBACK_1(OptionsMenu::onResolutionChanged, this));

	this->closeButton->setClickCallback(CC_CALLBACK_1(OptionsMenu::onCloseClick, this));
	this->returnButton->setClickCallback(CC_CALLBACK_1(OptionsMenu::onCloseClick, this));

	this->addChild(this->background);
	this->addChild(this->optionsWindow);
	this->addChild(this->titleLabel);
	this->addChild(this->closeButton);
	this->addChild(this->musicIcon);
	this->addChild(this->soundIcon);
	this->addChild(this->soundSlider);
	this->addChild(this->musicSlider);
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

	this->addChild(this->returnButton);

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

OptionsMenu::~OptionsMenu()
{
}

void OptionsMenu::onEnter()
{
	Hud::onEnter();

	float delay = 0.1f;
	float duration = 0.25f;

	GameUtils::fadeInObject(this->optionsWindow, delay, duration);
	GameUtils::fadeInObject(this->titleLabel, delay, duration);
	GameUtils::fadeInObject(this->closeButton, delay, duration);
	GameUtils::fadeInObject(this->musicIcon, delay, duration);
	GameUtils::fadeInObject(this->soundIcon, delay, duration);
	GameUtils::fadeInObject(this->musicSlider, delay, duration);
	GameUtils::fadeInObject(this->soundSlider, delay, duration);
	GameUtils::fadeInObject(this->fullScreenLabel, delay, duration);
	GameUtils::fadeInObject(this->fullScreenButton, delay, duration);
	GameUtils::fadeInObject(this->returnButton, delay, duration);

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

void OptionsMenu::initializeListeners()
{
	Hud::initializeListeners();

	EventListenerKeyboard* keyboardListener = EventListenerKeyboard::create();

	keyboardListener->onKeyPressed = CC_CALLBACK_2(OptionsMenu::onKeyPressed, this);

	this->addEventListener(keyboardListener);
}

void OptionsMenu::initializePositions()
{
	Hud::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->optionsWindow->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	this->titleLabel->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 + 286.0f));
	this->closeButton->setPosition(Vec2(visibleSize.width / 2 + 302.0f, visibleSize.height / 2 + 228.0f));

	this->soundIcon->setPosition(Vec2(visibleSize.width / 2 - 276.0f, visibleSize.height / 2 + 144.0f));
	this->musicIcon->setPosition(Vec2(visibleSize.width / 2 - 276.0f, visibleSize.height / 2 + 64.0f));
	this->soundSlider->setPosition(Vec2(visibleSize.width / 2 + 32.0f, visibleSize.height / 2 + 144.0f));
	this->musicSlider->setPosition(Vec2(visibleSize.width / 2 + 32.0f, visibleSize.height / 2 + 64.0f));
	this->fullScreenButton->setPosition(Vec2(visibleSize.width / 2 - 248.0f, visibleSize.height / 2 - 8.0f));
	this->fullScreenLabel->setPosition(Vec2(visibleSize.width / 2 - 112.0f, visibleSize.height / 2 - 8.0f));

	const float spacing = 140.0f;
	const float base = 225.0f;
	const float baseY = -64.0f;
	const float offsetY = 48.0f;
	const float textOffset = 64.0f;

	this->label1080x768->setPosition(Vec2(visibleSize.width / 2 - base + spacing * 0, visibleSize.height / 2 + baseY));
	this->label1152x864->setPosition(Vec2(visibleSize.width / 2 - base + spacing * 1, visibleSize.height / 2 + baseY));
	this->label1280x720->setPosition(Vec2(visibleSize.width / 2 - base + spacing * 2, visibleSize.height / 2 + baseY));
	this->label1280x960->setPosition(Vec2(visibleSize.width / 2 - base + spacing * 3, visibleSize.height / 2 + baseY));
	this->option1080x768->setPosition(Vec2(visibleSize.width / 2 - (base + textOffset) + spacing * 0, visibleSize.height / 2 + baseY));
	this->option1152x864->setPosition(Vec2(visibleSize.width / 2 - (base + textOffset) + spacing * 1, visibleSize.height / 2 + baseY));
	this->option1280x720->setPosition(Vec2(visibleSize.width / 2 - (base + textOffset) + spacing * 2, visibleSize.height / 2 + baseY));
	this->option1280x960->setPosition(Vec2(visibleSize.width / 2 - (base + textOffset) + spacing * 3, visibleSize.height / 2 + baseY));

	this->label1280x1024->setPosition(Vec2(visibleSize.width / 2 - base + spacing * 0, visibleSize.height / 2 + baseY - offsetY));
	this->label1440x900->setPosition(Vec2(visibleSize.width / 2 - base + spacing * 1, visibleSize.height / 2 + baseY - offsetY));
	this->label1600x900->setPosition(Vec2(visibleSize.width / 2 - base + spacing * 2, visibleSize.height / 2 + baseY - offsetY));
	this->label1600x1024->setPosition(Vec2(visibleSize.width / 2 - base + spacing * 3, visibleSize.height / 2 + baseY - offsetY));
	this->option1280x1024->setPosition(Vec2(visibleSize.width / 2 - (base + textOffset) + spacing * 0, visibleSize.height / 2 + baseY - offsetY));
	this->option1440x900->setPosition(Vec2(visibleSize.width / 2 - (base + textOffset) + spacing * 1, visibleSize.height / 2 + baseY - offsetY));
	this->option1600x900->setPosition(Vec2(visibleSize.width / 2 - (base + textOffset) + spacing * 2, visibleSize.height / 2 + baseY - offsetY));
	this->option1600x1024->setPosition(Vec2(visibleSize.width / 2 - (base + textOffset) + spacing * 3, visibleSize.height / 2 + baseY - offsetY));

	this->label1920x1080->setPosition(Vec2(visibleSize.width / 2 - base + spacing * 0, visibleSize.height / 2 + baseY - offsetY * 2));
	this->label2560x1440->setPosition(Vec2(visibleSize.width / 2 - base + spacing * 1, visibleSize.height / 2 + baseY - offsetY * 2));
	this->label3840x2160->setPosition(Vec2(visibleSize.width / 2 - base + spacing * 2, visibleSize.height / 2 + baseY - offsetY * 2));
	this->option1920x1080->setPosition(Vec2(visibleSize.width / 2 - (base + textOffset) + spacing * 0, visibleSize.height / 2 + baseY - offsetY * 2));
	this->option2560x1440->setPosition(Vec2(visibleSize.width / 2 - (base + textOffset) + spacing * 1, visibleSize.height / 2 + baseY - offsetY * 2));
	this->option3840x2160->setPosition(Vec2(visibleSize.width / 2 - (base + textOffset) + spacing * 2, visibleSize.height / 2 + baseY - offsetY * 2));

	this->returnButton->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 - offsetY * 5));
}

void OptionsMenu::setBackClickCallback(std::function<void()> backClickCallback)
{
	this->backClickCallback = backClickCallback;
}

bool OptionsMenu::onFullScreenChanged(CCheckbox* checkbox, bool isFullScreen)
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

void OptionsMenu::onResolutionChanged(CRadioButton* radioButton)
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

void OptionsMenu::onSoundVolumeUpdate(float soundVolume)
{
	SoundManager::setSoundVolume(soundVolume);
}

void OptionsMenu::onMusicVolumeUpdate(float musicVolume)
{
	SoundManager::setMusicVolume(musicVolume);
}

void OptionsMenu::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	if (!GameUtils::isVisible(this))
	{
		return;
	}

	switch (keyCode)
	{
		case EventKeyboard::KeyCode::KEY_ESCAPE:
		{
			event->stopPropagation();
			this->onMenuExit();
			break;
		}
		default:
		{
			break;
		}
	}
}

void OptionsMenu::onCloseClick(MenuSprite* menuSprite)
{
	this->onMenuExit();
}

void OptionsMenu::onMenuExit()
{
	ConfigManager::save();

	if (this->backClickCallback != nullptr)
	{
		this->backClickCallback();
	}
}

void OptionsMenu::showResolutionOptions()
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

void OptionsMenu::hideResolutionOptions()
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
