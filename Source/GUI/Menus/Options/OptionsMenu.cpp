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
	this->fullScreenLabel = MenuLabel::create("Full Screen Mode", Resources::Fonts_Montserrat_Medium, menuFontSize);
	this->windowedLabel = MenuLabel::create("Windowed Mode", Resources::Fonts_Montserrat_Medium, menuFontSize);
	this->exitLabel = MenuLabel::create("Return", Resources::Fonts_Montserrat_Medium, menuFontSize);
	this->closeButton = MenuSprite::create(Resources::Menus_Buttons_CloseButton, Resources::Menus_Buttons_CloseButtonHover, Resources::Menus_Buttons_CloseButtonClick);

	this->fullScreenLabel->SetCallback(CC_CALLBACK_1(OptionsMenu::OnMenuClick, this));
	this->windowedLabel->SetCallback(CC_CALLBACK_1(OptionsMenu::OnMenuClick, this));
	this->exitLabel->SetCallback(CC_CALLBACK_1(OptionsMenu::OnMenuClick, this));

	this->closeButton->SetClickCallback(CC_CALLBACK_1(OptionsMenu::OnCloseClick, this));
	this->closeButton->SetClickSound(Resources::Sounds_ClickBack1);

	this->mouse = Mouse::create();
	this->clickableMenus = new vector<MenuSprite*>();

	this->clickableMenus->push_back(this->closeButton);

	this->addChild(this->background);
	this->addChild(this->closeButton);
	this->addChild(this->fullScreenLabel);
	this->addChild(this->windowedLabel);
	this->addChild(this->exitLabel);
	this->addChild(this->mouse);

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
}

void OptionsMenu::InitializeListeners()
{
	EventListenerKeyboard* listener = EventListenerKeyboard::create();
	EventListenerMouse* mouseListener = EventListenerMouse::create();

	mouseListener->onMouseMove = CC_CALLBACK_1(OptionsMenu::OnMouseMove, this);
	listener->onKeyPressed = CC_CALLBACK_2(OptionsMenu::OnKeyPressed, this);

	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(mouseListener, this);
}

void OptionsMenu::InitializePositions()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	this->closeButton->setPosition(Vec2(origin.x + visibleSize.width / 2 + 302.0f, origin.y + visibleSize.height / 2 + 228.0f));
	this->fullScreenLabel->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2 - this->fullScreenLabel->getContentSize().height / 2 + menuOffset + spacing * 0));
	this->windowedLabel->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2 - this->windowedLabel->getContentSize().height / 2 + menuOffset + spacing * 1));
	this->exitLabel->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2 - this->exitLabel->getContentSize().height / 2 + menuOffset + spacing * 2));
	this->background->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
}

void OptionsMenu::OnMenuClick(MenuLabel* menuLabel)
{
	if (menuLabel == this->fullScreenLabel)
	{
		ConfigManager::SetResolution(ConfigManager::ResolutionSetting::FullScreen);
		this->InitializePositions();
	}
	else if (menuLabel == this->windowedLabel)
	{
		ConfigManager::SetResolution(ConfigManager::ResolutionSetting::R1080x768);
		this->InitializePositions();
	}
	else if (menuLabel == this->exitLabel)
	{
		Director::getInstance()->popScene();
	}
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

void OptionsMenu::OnMouseMove(EventMouse* event)
{
	this->mouse->SetCanClick(false);

	for (std::vector<MenuSprite*>::iterator it = this->clickableMenus->begin(); it != this->clickableMenus->end(); ++it)
	{
		MenuSprite* menuSprite = *it;

		if (menuSprite->isVisible() && Utils::Intersects(menuSprite, Vec2(event->getCursorX(), event->getCursorY())))
		{
			this->mouse->SetCanClick(true);
			return;
		}
	}
}

