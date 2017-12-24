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
	this->fullScreenLabel = MenuLabel::create("Full Screen", Resources::Fonts_Montserrat_Medium, menuFontSize);
	this->closeButton = MenuSprite::create(Resources::Menus_Buttons_CloseButton, Resources::Menus_Buttons_CloseButtonHover, Resources::Menus_Buttons_CloseButtonClick);

	this->musicIcon = Sprite::create(Resources::Menus_OptionsMenu_MusicIcon);
	this->soundIcon = Sprite::create(Resources::Menus_OptionsMenu_SoundIcon);

	this->musicSlider = Slider::create(SoundManager::GetInstance()->GetMusicVolume());
	this->soundSlider = Slider::create(SoundManager::GetInstance()->GetSoundVolume());

	this->fullScreenButton = ToggleButton::create(ConfigManager::GetInstance()->GetResolution() == ConfigManager::FullScreen ? true : false, CC_CALLBACK_1(OptionsMenu::OnFullScreenChanged, this));

	this->label1080x768 = Label::create("1080x768", Resources::Fonts_Montserrat_Medium, 14);
	this->label1152x864 = Label::create("1152x864", Resources::Fonts_Montserrat_Medium, 14);
	this->label1280x720 = Label::create("1280x720", Resources::Fonts_Montserrat_Medium, 14);
	this->label1280x960 = Label::create("1280x960", Resources::Fonts_Montserrat_Medium, 14);
	this->label1280x1024 = Label::create("1280x1024", Resources::Fonts_Montserrat_Medium, 14);
	this->label1440x900 = Label::create("1440x900", Resources::Fonts_Montserrat_Medium, 14);
	this->label1600x900 = Label::create("1600x900", Resources::Fonts_Montserrat_Medium, 14);
	this->label1600x1024 = Label::create("1600x1024", Resources::Fonts_Montserrat_Medium, 14);
	this->label1920x1080 = Label::create("1920x1080", Resources::Fonts_Montserrat_Medium, 14);

	this->option1080x768 = RadioButton::create(this->resolutionGroupId);
	this->option1152x864 = RadioButton::create(this->resolutionGroupId);
	this->option1280x720 = RadioButton::create(this->resolutionGroupId);
	this->option1280x960 = RadioButton::create(this->resolutionGroupId);
	this->option1280x1024 = RadioButton::create(this->resolutionGroupId);
	this->option1440x900 = RadioButton::create(this->resolutionGroupId);
	this->option1600x900 = RadioButton::create(this->resolutionGroupId);
	this->option1600x1024 = RadioButton::create(this->resolutionGroupId);
	this->option1920x1080 = RadioButton::create(this->resolutionGroupId);

	this->exitButton = MenuSprite::create(Resources::Menus_OptionsMenu_ExitButton, Resources::Menus_OptionsMenu_ExitButtonHover, Resources::Menus_OptionsMenu_ExitButtonClick);

	this->musicSlider->SetProgressUpdateCallback(CC_CALLBACK_1(OptionsMenu::OnMusicVolumeUpdate, this));
	this->soundSlider->SetProgressUpdateCallback(CC_CALLBACK_1(OptionsMenu::OnSoundVolumeUpdate, this));

	this->option1080x768->SetCheckCallback(CC_CALLBACK_1(OptionsMenu::OnResolutionChanged, this));
	this->option1152x864->SetCheckCallback(CC_CALLBACK_1(OptionsMenu::OnResolutionChanged, this));
	this->option1600x1024->SetCheckCallback(CC_CALLBACK_1(OptionsMenu::OnResolutionChanged, this));
	this->option1280x720->SetCheckCallback(CC_CALLBACK_1(OptionsMenu::OnResolutionChanged, this));
	this->option1280x960->SetCheckCallback(CC_CALLBACK_1(OptionsMenu::OnResolutionChanged, this));
	this->option1280x1024->SetCheckCallback(CC_CALLBACK_1(OptionsMenu::OnResolutionChanged, this));
	this->option1440x900->SetCheckCallback(CC_CALLBACK_1(OptionsMenu::OnResolutionChanged, this));
	this->option1600x900->SetCheckCallback(CC_CALLBACK_1(OptionsMenu::OnResolutionChanged, this));
	this->option1600x1024->SetCheckCallback(CC_CALLBACK_1(OptionsMenu::OnResolutionChanged, this));
	this->option1920x1080->SetCheckCallback(CC_CALLBACK_1(OptionsMenu::OnResolutionChanged, this));

	this->closeButton->SetClickCallback(CC_CALLBACK_1(OptionsMenu::OnCloseClick, this));
	this->closeButton->SetClickSound(Resources::Sounds_ClickBack1);

	this->exitButton->SetClickCallback(CC_CALLBACK_1(OptionsMenu::OnCloseClick, this));
	this->exitButton->SetClickSound(Resources::Sounds_ClickBack1);

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

	switch (ConfigManager::GetInstance()->GetResolution())
	{
	case ConfigManager::ResolutionSetting::R1080x768:
		this->ShowResolutionOptions();
		this->option1080x768->Check();
		break;
	case ConfigManager::ResolutionSetting::R1152x864:
		this->ShowResolutionOptions();
		this->option1152x864->Check();
		break;
	case ConfigManager::ResolutionSetting::R1280x720:
		this->ShowResolutionOptions();
		this->option1280x720->Check();
		break;
	case ConfigManager::ResolutionSetting::R1280x960:
		this->ShowResolutionOptions();
		this->option1280x960->Check();
		break;
	case ConfigManager::ResolutionSetting::R1280x1024:
		this->ShowResolutionOptions();
		this->option1280x1024->Check();
		break;
	case ConfigManager::ResolutionSetting::R1440x900:
		this->ShowResolutionOptions();
		this->option1440x900->Check();
		break;
	case ConfigManager::ResolutionSetting::R1600x900:
		this->ShowResolutionOptions();
		this->option1600x900->Check();
		break;
	case ConfigManager::ResolutionSetting::R1600x1024:
		this->ShowResolutionOptions();
		this->option1600x1024->Check();
		break;
	case ConfigManager::ResolutionSetting::R1920x1080:
		this->ShowResolutionOptions();
		this->option1920x1080->Check();
		break;
	case ConfigManager::ResolutionSetting::FullScreen:
	default:
		this->HideResolutionOptions();
		break;
	}

	this->InitializePositions();
	this->InitializeListeners();
}

OptionsMenu::~OptionsMenu()
{
}

void OptionsMenu::onEnter()
{
	FadeScene::onEnter();

	float delay = 0.25f;
	float duration = 0.35f;

	Utils::FadeInObject(this->optionsWindow, delay, duration);
	Utils::FadeInObject(this->closeButton, delay, duration);
	Utils::FadeInObject(this->musicIcon, delay, duration);
	Utils::FadeInObject(this->soundIcon, delay, duration);
	Utils::FadeInObject(this->musicSlider, delay, duration);
	Utils::FadeInObject(this->soundSlider, delay, duration);
	Utils::FadeInObject(this->fullScreenLabel, delay, duration);
	Utils::FadeInObject(this->fullScreenButton, delay, duration);
	Utils::FadeInObject(this->exitButton, delay, duration);

	Utils::FadeInObject(this->label1080x768, delay, duration);
	Utils::FadeInObject(this->label1152x864, delay, duration);
	Utils::FadeInObject(this->label1280x720, delay, duration);
	Utils::FadeInObject(this->label1280x960, delay, duration);
	Utils::FadeInObject(this->label1280x1024, delay, duration);
	Utils::FadeInObject(this->label1440x900, delay, duration);
	Utils::FadeInObject(this->label1600x900, delay, duration);
	Utils::FadeInObject(this->label1600x1024, delay, duration);
	Utils::FadeInObject(this->label1920x1080, delay, duration);

	Utils::FadeInObject(this->option1080x768, delay, duration);
	Utils::FadeInObject(this->option1152x864, delay, duration);
	Utils::FadeInObject(this->option1280x720, delay, duration);
	Utils::FadeInObject(this->option1280x960, delay, duration);
	Utils::FadeInObject(this->option1280x1024, delay, duration);
	Utils::FadeInObject(this->option1440x900, delay, duration);
	Utils::FadeInObject(this->option1600x900, delay, duration);
	Utils::FadeInObject(this->option1600x1024, delay, duration);
	Utils::FadeInObject(this->option1920x1080, delay, duration);

	this->background->addChild(MenuBackground::ClaimInstance());

	this->InitializePositions();

	this->addChild(Mouse::claimInstance());
}

void OptionsMenu::OnFullScreenChanged(bool isFullScreen)
{
	if (isFullScreen)
	{
		ConfigManager::GetInstance()->SetResolution(ConfigManager::ResolutionSetting::FullScreen);
		this->InitializePositions();
		this->HideResolutionOptions();
	}
	else
	{
		ConfigManager::ResolutionSetting resolution = ConfigManager::GetInstance()->GetResolution();

		// Default non-full screen resolution
		if (resolution == ConfigManager::ResolutionSetting::FullScreen)
		{
			resolution = ConfigManager::ResolutionSetting::R1080x768;
			this->option1080x768->Check();
		}

		this->InitializePositions();
		this->ShowResolutionOptions();
	}
}

void OptionsMenu::OnResolutionChanged(RadioButton* radioButton)
{
	if (radioButton == this->option1080x768)
	{
		ConfigManager::GetInstance()->SetResolution(ConfigManager::ResolutionSetting::R1080x768);
	}
	else if (radioButton == this->option1152x864)
	{
		ConfigManager::GetInstance()->SetResolution(ConfigManager::ResolutionSetting::R1152x864);
	}
	else if (radioButton == this->option1280x720)
	{
		ConfigManager::GetInstance()->SetResolution(ConfigManager::ResolutionSetting::R1280x720);
	}
	else if (radioButton == this->option1280x960)
	{
		ConfigManager::GetInstance()->SetResolution(ConfigManager::ResolutionSetting::R1280x960);
	}
	else if (radioButton == this->option1280x1024)
	{
		ConfigManager::GetInstance()->SetResolution(ConfigManager::ResolutionSetting::R1280x1024);
	}
	else if (radioButton == this->option1440x900)
	{
		ConfigManager::GetInstance()->SetResolution(ConfigManager::ResolutionSetting::R1440x900);
	}
	else if (radioButton == this->option1600x900)
	{
		ConfigManager::GetInstance()->SetResolution(ConfigManager::ResolutionSetting::R1600x900);
	}
	else if (radioButton == this->option1600x1024)
	{
		ConfigManager::GetInstance()->SetResolution(ConfigManager::ResolutionSetting::R1600x1024);
	}
	else if (radioButton == this->option1920x1080)
	{
		ConfigManager::GetInstance()->SetResolution(ConfigManager::ResolutionSetting::R1920x1080);
	}

	this->InitializePositions();
}

void OptionsMenu::InitializeListeners()
{
	EventListenerKeyboard* listener = EventListenerKeyboard::create();

	listener->onKeyPressed = CC_CALLBACK_2(OptionsMenu::OnKeyPressed, this);

	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
}

void OptionsMenu::InitializePositions()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	this->optionsWindow->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
	this->closeButton->setPosition(Vec2(origin.x + visibleSize.width / 2 + 302.0f, origin.y + visibleSize.height / 2 + 228.0f));

	this->soundIcon->setPosition(Vec2(origin.x + visibleSize.width / 2 - 276.0f, origin.y + visibleSize.height / 2 + 144.0f));
	this->musicIcon->setPosition(Vec2(origin.x + visibleSize.width / 2 - 276.0f, origin.y + visibleSize.height / 2 + 64.0f));
	this->soundSlider->setPosition(Vec2(origin.x + visibleSize.width / 2 + 32.0f, origin.y + visibleSize.height / 2 + 144.0f));
	this->musicSlider->setPosition(Vec2(origin.x + visibleSize.width / 2 + 32.0f, origin.y + visibleSize.height / 2 + 64.0f));
	this->fullScreenLabel->setPosition(Vec2(origin.x + visibleSize.width / 2 - 216.0f, origin.y + visibleSize.height / 2 - 8.0f));
	this->fullScreenButton->setPosition(Vec2(origin.x + visibleSize.width / 2 - 32.0f, origin.y + visibleSize.height / 2 - 8.0f));

	const float spacing = 128.0f;
	const float base = 232.0f;
	const float baseY = -64.0f;
	const float offsetY = 48.0f;
	const float textOffset = 64.0f;

	this->label1080x768->setPosition(Vec2(origin.x + visibleSize.width / 2 - base + spacing * 0, origin.y + visibleSize.height / 2 + baseY));
	this->label1152x864->setPosition(Vec2(origin.x + visibleSize.width / 2 - base + spacing * 0, origin.y + visibleSize.height / 2 + baseY - offsetY));
	this->label1280x720->setPosition(Vec2(origin.x + visibleSize.width / 2 - base + spacing * 1, origin.y + visibleSize.height / 2 + baseY));
	this->label1280x960->setPosition(Vec2(origin.x + visibleSize.width / 2 - base + spacing * 1, origin.y + visibleSize.height / 2 + baseY - offsetY));
	this->label1280x1024->setPosition(Vec2(origin.x + visibleSize.width / 2 - base + spacing * 2, origin.y + visibleSize.height / 2 + baseY));
	this->label1440x900->setPosition(Vec2(origin.x + visibleSize.width / 2 - base + spacing * 2, origin.y + visibleSize.height / 2 + baseY - offsetY));
	this->label1600x900->setPosition(Vec2(origin.x + visibleSize.width / 2 - base + spacing * 3, origin.y + visibleSize.height / 2 + baseY));
	this->label1600x1024->setPosition(Vec2(origin.x + visibleSize.width / 2 - base + spacing * 3, origin.y + visibleSize.height / 2 + baseY - offsetY));
	this->label1920x1080->setPosition(Vec2(origin.x + visibleSize.width / 2 - base + spacing * 4, origin.y + visibleSize.height / 2 + baseY));

	this->option1080x768->setPosition(Vec2(origin.x + visibleSize.width / 2 - (base + textOffset) + spacing * 0, origin.y + visibleSize.height / 2 + baseY));
	this->option1152x864->setPosition(Vec2(origin.x + visibleSize.width / 2 - (base + textOffset) + spacing * 0, origin.y + visibleSize.height / 2 + baseY - offsetY));
	this->option1280x720->setPosition(Vec2(origin.x + visibleSize.width / 2 - (base + textOffset) + spacing * 1, origin.y + visibleSize.height / 2 + baseY));
	this->option1280x960->setPosition(Vec2(origin.x + visibleSize.width / 2 - (base + textOffset) + spacing * 1, origin.y + visibleSize.height / 2 + baseY - offsetY));
	this->option1280x1024->setPosition(Vec2(origin.x + visibleSize.width / 2 - (base + textOffset) + spacing * 2, origin.y + visibleSize.height / 2 + baseY));
	this->option1440x900->setPosition(Vec2(origin.x + visibleSize.width / 2 - (base + textOffset) + spacing * 2, origin.y + visibleSize.height / 2 + baseY - offsetY));
	this->option1600x900->setPosition(Vec2(origin.x + visibleSize.width / 2 - (base + textOffset) + spacing * 3, origin.y + visibleSize.height / 2 + baseY));
	this->option1600x1024->setPosition(Vec2(origin.x + visibleSize.width / 2 - (base + textOffset) + spacing * 3, origin.y + visibleSize.height / 2 + baseY - offsetY));
	this->option1920x1080->setPosition(Vec2(origin.x + visibleSize.width / 2 - (base + textOffset) + spacing * 4, origin.y + visibleSize.height / 2 + baseY));

	this->exitButton->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2 - 196.0f));

	this->musicSlider->InitializePositions();
	this->soundSlider->InitializePositions();

	MenuBackground::GetInstance()->InitializePositions();
}

void OptionsMenu::OnSoundVolumeUpdate(float soundVolume)
{
	SoundManager::GetInstance()->SetSoundVolume(soundVolume);
}

void OptionsMenu::OnMusicVolumeUpdate(float musicVolume)
{
	SoundManager::GetInstance()->SetMusicVolume(musicVolume);
}

void OptionsMenu::OnKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	switch (keyCode)
	{
	case EventKeyboard::KeyCode::KEY_ESCAPE:
		Director::getInstance()->popScene();
		ConfigManager::GetInstance()->Save();
		break;
	}
}

void OptionsMenu::OnCloseClick(MenuSprite* menuSprite)
{
	Director::getInstance()->popScene();
	ConfigManager::GetInstance()->Save();
}

void OptionsMenu::ShowResolutionOptions()
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

void OptionsMenu::HideResolutionOptions()
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
