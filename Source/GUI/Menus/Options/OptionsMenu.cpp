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

	// TODO: Load fullscreen/resolution setting
	this->fullScreenButton = ToggleButton::create(true, CC_CALLBACK_1(OptionsMenu::OnFullScreenChanged, this));
	this->exitButton = MenuSprite::create(Resources::Menus_OptionsMenu_ExitButton, Resources::Menus_OptionsMenu_ExitButtonHover, Resources::Menus_OptionsMenu_ExitButtonClick);

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
	this->addChild(this->exitButton);

	this->InitializePositions();
	this->InitializeListeners();
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
		ConfigManager::SetResolution(ConfigManager::ResolutionSetting::FullScreen);
		this->InitializePositions();
	}
	else
	{
		// TODO: Load saved resolution setting
		ConfigManager::SetResolution(ConfigManager::ResolutionSetting::R1080x768);
		this->InitializePositions();
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

	this->soundIcon->setPosition(Vec2(origin.x + visibleSize.width / 2 - 276.0f, origin.y + visibleSize.height / 2 + 128.0f));
	this->musicIcon->setPosition(Vec2(origin.x + visibleSize.width / 2 - 276.0f, origin.y + visibleSize.height / 2 + 48.0f));
	this->soundSlider->setPosition(Vec2(origin.x + visibleSize.width / 2 + 32.0f, origin.y + visibleSize.height / 2 + 128.0f));
	this->musicSlider->setPosition(Vec2(origin.x + visibleSize.width / 2 + 32.0f, origin.y + visibleSize.height / 2 + 48.0f));
	this->fullScreenLabel->setPosition(Vec2(origin.x + visibleSize.width / 2 - 96.0f, origin.y + visibleSize.height / 2 - 32.0f));
	this->fullScreenButton->setPosition(Vec2(origin.x + visibleSize.width / 2 + 128.0f, origin.y + visibleSize.height / 2 - 32.0f));
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
		break;
	}
}

void OptionsMenu::OnCloseClick(MenuSprite* menuSprite)
{
	Director::getInstance()->popScene();
}
