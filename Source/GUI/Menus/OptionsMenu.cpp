#include "OptionsMenu.h"

OptionsMenu::OptionsMenu()
{
	this->background = Sprite::create(Resources::GUI_OptionsMenu_OptionsMenu);
	this->titleLabel = new MenuLabel("Options", Resources::Fonts_Marker_Felt, titleFontSize);
	this->fullScreenLabel = new MenuLabel("Full Screen Mode", Resources::Fonts_Marker_Felt, menuFontSize, CC_CALLBACK_1(OptionsMenu::OnMenuClick, this));
	this->windowedLabel = new MenuLabel("Windowed Mode", Resources::Fonts_Marker_Felt, menuFontSize, CC_CALLBACK_1(OptionsMenu::OnMenuClick, this));
	this->exitLabel = new MenuLabel("Exit", Resources::Fonts_Marker_Felt, menuFontSize, CC_CALLBACK_1(OptionsMenu::OnMenuClick, this));

	this->mouse = new Mouse();
	this->clickableMenus = new vector<MenuLabel*>();

	this->clickableMenus->push_back(this->fullScreenLabel);
	this->clickableMenus->push_back(this->windowedLabel);
	this->clickableMenus->push_back(this->exitLabel);

	this->addChild(this->background);
	this->addChild(this->titleLabel);
	this->addChild(this->fullScreenLabel);
	this->addChild(this->windowedLabel);
	this->addChild(this->exitLabel);
	this->addChild(this->mouse);

	this->InitializePositions();
}

OptionsMenu::~OptionsMenu()
{
}

void OptionsMenu::onEnter()
{
	Scene::onEnter();
	this->InitializeListeners();
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

	this->titleLabel->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2 - this->titleLabel->getContentSize().height + menuOffset - spacing * 1.5));
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
		Director::getInstance()->replaceScene(new TitleScreen());
	}
}

void OptionsMenu::OnKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	switch (keyCode) {
	case EventKeyboard::KeyCode::KEY_ESCAPE:
		Director::getInstance()->replaceScene(new TitleScreen());
		break;
	}
}
