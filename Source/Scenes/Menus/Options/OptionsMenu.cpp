#include "OptionsMenu.h"

OptionsMenu * OptionsMenu::create()
{
	OptionsMenu* optionsMenu = new OptionsMenu();

	optionsMenu->autorelease();

	return optionsMenu;
}

OptionsMenu::OptionsMenu()
{
	this->background = Node::create();
	this->optionsWindow = Sprite::create(Resources::Menus_OptionsMenu_OptionsMenu);
	this->fullScreenLabel = Label::create("Full Screen", Resources::Fonts_Montserrat_Medium, menuFontSize);
	this->closeButton = MenuSprite::create(Resources::Menus_Buttons_CloseButton, Resources::Menus_Buttons_CloseButtonHover, Resources::Menus_Buttons_CloseButtonClick);

	this->fullScreenLabel->enableOutline(Color4B::BLACK, 2.0f);

	this->musicIcon = Sprite::create(Resources::Menus_OptionsMenu_MusicIcon);
	this->soundIcon = Sprite::create(Resources::Menus_OptionsMenu_SoundIcon);

	this->musicSlider = CSlider::create(SoundManager::getMusicVolume());
	this->soundSlider = CSlider::create(SoundManager::getSoundVolume());

	MenuSprite* uncheckedMenuSprite = MenuSprite::create(Resources::Menus_OptionsMenu_ToggleButtonOff, Resources::Menus_OptionsMenu_ToggleButtonOffHover, Resources::Menus_OptionsMenu_ToggleButtonOffClick);
	MenuSprite* checkedMenuSprite = MenuSprite::create(Resources::Menus_OptionsMenu_ToggleButtonOn, Resources::Menus_OptionsMenu_ToggleButtonOffHover, Resources::Menus_OptionsMenu_ToggleButtonOffClick);
	this->fullScreenButton = CCheckbox::create(uncheckedMenuSprite, checkedMenuSprite, ConfigManager::getIsFullScreen(), CC_CALLBACK_2(OptionsMenu::onFullScreenChanged, this));

	this->label1080x768 = Label::create("1080x768", Resources::Fonts_Montserrat_Medium, 14);
	this->label1152x864 = Label::create("1152x864", Resources::Fonts_Montserrat_Medium, 14);
	this->label1280x720 = Label::create("1280x720", Resources::Fonts_Montserrat_Medium, 14);
	this->label1280x960 = Label::create("1280x960", Resources::Fonts_Montserrat_Medium, 14);
	this->label1280x1024 = Label::create("1280x1024", Resources::Fonts_Montserrat_Medium, 14);
	this->label1440x900 = Label::create("1440x900", Resources::Fonts_Montserrat_Medium, 14);
	this->label1600x900 = Label::create("1600x900", Resources::Fonts_Montserrat_Medium, 14);
	this->label1600x1024 = Label::create("1600x1024", Resources::Fonts_Montserrat_Medium, 14);
	this->label1920x1080 = Label::create("1920x1080", Resources::Fonts_Montserrat_Medium, 14);

	this->option1080x768 = CRadioButton::create(this->resolutionGroupId);
	this->option1152x864 = CRadioButton::create(this->resolutionGroupId);
	this->option1280x720 = CRadioButton::create(this->resolutionGroupId);
	this->option1280x960 = CRadioButton::create(this->resolutionGroupId);
	this->option1280x1024 = CRadioButton::create(this->resolutionGroupId);
	this->option1440x900 = CRadioButton::create(this->resolutionGroupId);
	this->option1600x900 = CRadioButton::create(this->resolutionGroupId);
	this->option1600x1024 = CRadioButton::create(this->resolutionGroupId);
	this->option1920x1080 = CRadioButton::create(this->resolutionGroupId);

	this->exitButton = MenuSprite::create(Resources::Menus_Buttons_GenericButton, Resources::Menus_Buttons_GenericButtonHover, Resources::Menus_Buttons_GenericButtonClick);

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

	this->closeButton->setClickCallback(CC_CALLBACK_1(OptionsMenu::onCloseClick, this));
	this->closeButton->setClickSound(Resources::Sounds_ClickBack1);

	this->exitButton->setClickCallback(CC_CALLBACK_1(OptionsMenu::onCloseClick, this));
	this->exitButton->setClickSound(Resources::Sounds_ClickBack1);

	this->addChild(this->background);
	this->addChild(this->optionsWindow);
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

	this->addChild(this->option1080x768);
	this->addChild(this->option1152x864);
	this->addChild(this->option1280x720);
	this->addChild(this->option1280x960);
	this->addChild(this->option1280x1024);
	this->addChild(this->option1440x900);
	this->addChild(this->option1600x900);
	this->addChild(this->option1600x1024);
	this->addChild(this->option1920x1080);

	this->addChild(this->exitButton);
	this->addChild(Mouse::create());

	switch (ConfigManager::getResolution())
	{
	case ConfigManager::ResolutionSetting::R1080x768:
		this->option1080x768->check();
		break;
	case ConfigManager::ResolutionSetting::R1152x864:
		this->option1152x864->check();
		break;
	case ConfigManager::ResolutionSetting::R1280x720:
		this->option1280x720->check();
		break;
	case ConfigManager::ResolutionSetting::R1280x960:
		this->option1280x960->check();
		break;
	case ConfigManager::ResolutionSetting::R1280x1024:
		this->option1280x1024->check();
		break;
	case ConfigManager::ResolutionSetting::R1440x900:
		this->option1440x900->check();
		break;
	case ConfigManager::ResolutionSetting::R1600x900:
		this->option1600x900->check();
		break;
	case ConfigManager::ResolutionSetting::R1600x1024:
		this->option1600x1024->check();
		break;
	case ConfigManager::ResolutionSetting::R1920x1080:
	default:
		this->option1920x1080->check();
		break;
	}

	if (ConfigManager::getIsFullScreen())
	{
		this->hideResolutionOptions();
	}
	else
	{
		this->showResolutionOptions();
	}

	this->setFadeSpeed(0.0f);
}

OptionsMenu::~OptionsMenu()
{
}

void OptionsMenu::onEnter()
{
	FadeScene::onEnter();

	float delay = 0.25f;
	float duration = 0.35f;

	GameUtils::fadeInObject(this->optionsWindow, delay, duration);
	GameUtils::fadeInObject(this->closeButton, delay, duration);
	GameUtils::fadeInObject(this->musicIcon, delay, duration);
	GameUtils::fadeInObject(this->soundIcon, delay, duration);
	GameUtils::fadeInObject(this->musicSlider, delay, duration);
	GameUtils::fadeInObject(this->soundSlider, delay, duration);
	GameUtils::fadeInObject(this->fullScreenLabel, delay, duration);
	GameUtils::fadeInObject(this->fullScreenButton, delay, duration);
	GameUtils::fadeInObject(this->exitButton, delay, duration);

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

	this->background->addChild(MenuBackground::claimInstance());

	this->initializePositions();
	this->initializeListeners();
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

	this->initializePositions();

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

	this->initializePositions();
}

void OptionsMenu::initializeListeners()
{
	this->getEventDispatcher()->removeEventListenersForTarget(this);

	EventListenerKeyboard* keyboardListener = EventListenerKeyboard::create();

	keyboardListener->onKeyPressed = CC_CALLBACK_2(OptionsMenu::onKeyPressed, this);

	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(keyboardListener, this);
}

void OptionsMenu::initializePositions()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->optionsWindow->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	this->closeButton->setPosition(Vec2(visibleSize.width / 2 + 302.0f, visibleSize.height / 2 + 228.0f));

	this->soundIcon->setPosition(Vec2(visibleSize.width / 2 - 276.0f, visibleSize.height / 2 + 144.0f));
	this->musicIcon->setPosition(Vec2(visibleSize.width / 2 - 276.0f, visibleSize.height / 2 + 64.0f));
	this->soundSlider->setPosition(Vec2(visibleSize.width / 2 + 32.0f, visibleSize.height / 2 + 144.0f));
	this->musicSlider->setPosition(Vec2(visibleSize.width / 2 + 32.0f, visibleSize.height / 2 + 64.0f));
	this->fullScreenLabel->setPosition(Vec2(visibleSize.width / 2 - 216.0f, visibleSize.height / 2 - 8.0f));
	this->fullScreenButton->setPosition(Vec2(visibleSize.width / 2 - 32.0f, visibleSize.height / 2 - 8.0f));

	const float spacing = 128.0f;
	const float base = 232.0f;
	const float baseY = -64.0f;
	const float offsetY = 48.0f;
	const float textOffset = 64.0f;

	this->label1080x768->setPosition(Vec2(visibleSize.width / 2 - base + spacing * 0, visibleSize.height / 2 + baseY));
	this->label1152x864->setPosition(Vec2(visibleSize.width / 2 - base + spacing * 0, visibleSize.height / 2 + baseY - offsetY));
	this->label1280x720->setPosition(Vec2(visibleSize.width / 2 - base + spacing * 1, visibleSize.height / 2 + baseY));
	this->label1280x960->setPosition(Vec2(visibleSize.width / 2 - base + spacing * 1, visibleSize.height / 2 + baseY - offsetY));
	this->label1280x1024->setPosition(Vec2(visibleSize.width / 2 - base + spacing * 2, visibleSize.height / 2 + baseY));
	this->label1440x900->setPosition(Vec2(visibleSize.width / 2 - base + spacing * 2, visibleSize.height / 2 + baseY - offsetY));
	this->label1600x900->setPosition(Vec2(visibleSize.width / 2 - base + spacing * 3, visibleSize.height / 2 + baseY));
	this->label1600x1024->setPosition(Vec2(visibleSize.width / 2 - base + spacing * 3, visibleSize.height / 2 + baseY - offsetY));
	this->label1920x1080->setPosition(Vec2(visibleSize.width / 2 - base + spacing * 4, visibleSize.height / 2 + baseY));

	this->option1080x768->setPosition(Vec2(visibleSize.width / 2 - (base + textOffset) + spacing * 0, visibleSize.height / 2 + baseY));
	this->option1152x864->setPosition(Vec2(visibleSize.width / 2 - (base + textOffset) + spacing * 0, visibleSize.height / 2 + baseY - offsetY));
	this->option1280x720->setPosition(Vec2(visibleSize.width / 2 - (base + textOffset) + spacing * 1, visibleSize.height / 2 + baseY));
	this->option1280x960->setPosition(Vec2(visibleSize.width / 2 - (base + textOffset) + spacing * 1, visibleSize.height / 2 + baseY - offsetY));
	this->option1280x1024->setPosition(Vec2(visibleSize.width / 2 - (base + textOffset) + spacing * 2, visibleSize.height / 2 + baseY));
	this->option1440x900->setPosition(Vec2(visibleSize.width / 2 - (base + textOffset) + spacing * 2, visibleSize.height / 2 + baseY - offsetY));
	this->option1600x900->setPosition(Vec2(visibleSize.width / 2 - (base + textOffset) + spacing * 3, visibleSize.height / 2 + baseY));
	this->option1600x1024->setPosition(Vec2(visibleSize.width / 2 - (base + textOffset) + spacing * 3, visibleSize.height / 2 + baseY - offsetY));
	this->option1920x1080->setPosition(Vec2(visibleSize.width / 2 - (base + textOffset) + spacing * 4, visibleSize.height / 2 + baseY));

	this->exitButton->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 - 196.0f));

	this->musicSlider->initializePositions();
	this->soundSlider->initializePositions();

	MenuBackground::getInstance()->initializePositions();
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
	switch (keyCode)
	{
	case EventKeyboard::KeyCode::KEY_ESCAPE:
		ConfigManager::save();
		event->stopPropagation();
		NavigationEvents::navigateBack();
		break;
	}
}

void OptionsMenu::onCloseClick(MenuSprite* menuSprite)
{
	ConfigManager::save();
	NavigationEvents::navigateBack();
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

	this->option1080x768->setVisible(false);
	this->option1152x864->setVisible(false);
	this->option1280x720->setVisible(false);
	this->option1280x960->setVisible(false);
	this->option1280x1024->setVisible(false);
	this->option1440x900->setVisible(false);
	this->option1600x900->setVisible(false);
	this->option1600x1024->setVisible(false);
	this->option1920x1080->setVisible(false);
}
