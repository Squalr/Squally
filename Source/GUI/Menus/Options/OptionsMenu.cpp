#include "OptionsMenu.h"

OptionsMenu * OptionsMenu::create()
{
	OptionsMenu* optionsMenu = new OptionsMenu();

	optionsMenu->autorelease();

	return optionsMenu;
}

OptionsMenu::OptionsMenu()
{
	this->background = Sprite::create(Resources::Menus_OptionsMenu_OptionsMenu);
	this->fullScreenLabel = MenuLabel::create("Full Screen", Resources::Fonts_Montserrat_Medium, menuFontSize);
	this->closeButton = MenuSprite::create(Resources::Menus_Buttons_CloseButton, Resources::Menus_Buttons_CloseButtonHover, Resources::Menus_Buttons_CloseButtonClick);

	this->musicIcon = Sprite::create(Resources::Menus_OptionsMenu_MusicIcon);
	this->soundIcon = Sprite::create(Resources::Menus_OptionsMenu_SoundIcon);

	this->musicSlider = Slider::create(SoundManager::GetInstance()->GetMusicVolume());
	this->soundSlider = Slider::create(SoundManager::GetInstance()->GetSoundVolume());

	this->exitButton = MenuSprite::create(Resources::Menus_OptionsMenu_ExitButton, Resources::Menus_OptionsMenu_ExitButtonHover, Resources::Menus_OptionsMenu_ExitButtonClick);
	this->label1080x768 = Label::create("1080x768", Resources::Fonts_Montserrat_Medium, 14);
	this->label1920x1080 = Label::create("1920x1080", Resources::Fonts_Montserrat_Medium, 14);
	this->resolutionGroup = RadioButtonGroup::create();
	this->option1080x768 = RadioButton::create(this->resolutionGroup);
	this->option1920x1080 = RadioButton::create(this->resolutionGroup);

	bool isFullScreen = false;

	switch (ConfigManager::GetInstance()->GetResolution())
	{
	case ConfigManager::ResolutionSetting::FullScreen:
		this->fullScreenButton = ToggleButton::create(true, CC_CALLBACK_1(OptionsMenu::OnFullScreenChanged, this));
		isFullScreen = true;
		break;
	default:
		this->fullScreenButton = ToggleButton::create(false, CC_CALLBACK_1(OptionsMenu::OnFullScreenChanged, this));
	}

	this->exitButton->SetClickCallback(CC_CALLBACK_1(OptionsMenu::OnCloseClick, this));
	this->exitButton->SetClickSound(Resources::Sounds_ClickBack1);

	this->closeButton->SetClickCallback(CC_CALLBACK_1(OptionsMenu::OnCloseClick, this));
	this->closeButton->SetClickSound(Resources::Sounds_ClickBack1);

	this->musicSlider->SetProgressUpdateCallback(CC_CALLBACK_1(OptionsMenu::OnMusicVolumeUpdate, this));
	this->soundSlider->SetProgressUpdateCallback(CC_CALLBACK_1(OptionsMenu::OnSoundVolumeUpdate, this));

	this->clickableMenus = new vector<MenuSprite*>();

	this->clickableMenus->push_back(this->closeButton);
	this->clickableMenus->push_back(this->exitButton);

	this->addChild(this->background);
	this->addChild(this->closeButton);
	this->addChild(this->musicIcon);
	this->addChild(this->soundIcon);
	this->addChild(this->soundSlider);
	this->addChild(this->musicSlider);
	this->addChild(this->fullScreenLabel);
	this->addChild(this->fullScreenButton);
	this->addChild(this->label1080x768);
	this->addChild(this->label1920x1080);
	this->addChild(this->option1080x768);
	this->addChild(this->option1920x1080);
	this->addChild(this->exitButton);

	this->InitializePositions();
	this->InitializeListeners();

	if (isFullScreen)
	{
		this->HideResolutionOptions();
	}
	else
	{
		this->ShowResolutionOptions();
	}
}

OptionsMenu::~OptionsMenu()
{
}

void OptionsMenu::onEnter()
{
	Scene::onEnter();

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
		// TODO: Load saved resolution setting
		ConfigManager::GetInstance()->SetResolution(ConfigManager::ResolutionSetting::R1080x768);
		this->InitializePositions();
		this->ShowResolutionOptions();
	}
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

	this->background->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
	this->closeButton->setPosition(Vec2(origin.x + visibleSize.width / 2 + 302.0f, origin.y + visibleSize.height / 2 + 228.0f));

	this->soundIcon->setPosition(Vec2(origin.x + visibleSize.width / 2 - 276.0f, origin.y + visibleSize.height / 2 + 144.0f));
	this->musicIcon->setPosition(Vec2(origin.x + visibleSize.width / 2 - 276.0f, origin.y + visibleSize.height / 2 + 64.0f));
	this->soundSlider->setPosition(Vec2(origin.x + visibleSize.width / 2 + 32.0f, origin.y + visibleSize.height / 2 + 144.0f));
	this->musicSlider->setPosition(Vec2(origin.x + visibleSize.width / 2 + 32.0f, origin.y + visibleSize.height / 2 + 64.0f));
	this->fullScreenLabel->setPosition(Vec2(origin.x + visibleSize.width / 2 - 96.0f, origin.y + visibleSize.height / 2 - 16.0f));
	this->fullScreenButton->setPosition(Vec2(origin.x + visibleSize.width / 2 + 128.0f, origin.y + visibleSize.height / 2 - 16.0f));
	this->label1080x768->setPosition(Vec2(origin.x + visibleSize.width / 2 - 196.0f, origin.y + visibleSize.height / 2 - 80.0f));
	this->label1920x1080->setPosition(Vec2(origin.x + visibleSize.width / 2 - 196.0f, origin.y + visibleSize.height / 2 - 128.0f));
	this->option1080x768->setPosition(Vec2(origin.x + visibleSize.width / 2 - 256.0f, origin.y + visibleSize.height / 2 - 80.0f));
	this->option1920x1080->setPosition(Vec2(origin.x + visibleSize.width / 2 - 256.0f, origin.y + visibleSize.height / 2 - 128.0f));
	this->exitButton->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2 - 196.0f));

	this->musicSlider->InitializePositions();
	this->soundSlider->InitializePositions();
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
	this->option1080x768->setVisible(true);
	this->option1920x1080->setVisible(true);
	this->label1080x768->setVisible(true);
	this->label1920x1080->setVisible(true);
}

void OptionsMenu::HideResolutionOptions()
{
	this->option1080x768->setVisible(false);
	this->option1920x1080->setVisible(false);
	this->label1080x768->setVisible(false);
	this->label1920x1080->setVisible(false);
}
