#include "OptionsMenu.h"

OptionsMenu::OptionsMenu()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	this->background = Sprite::create(Resources::GUI_OptionsMenu_OptionsMenu);
	this->titleLabel = new MenuLabel("Options", Resources::Fonts_Marker_Felt, titleFontSize);
	this->fullScreenLabel = new MenuLabel("Full Screen Mode", Resources::Fonts_Marker_Felt, menuFontSize, CC_CALLBACK_1(OptionsMenu::OnMenuClick, this));
	this->windowedLabel = new MenuLabel("Windowed Mode", Resources::Fonts_Marker_Felt, menuFontSize, CC_CALLBACK_1(OptionsMenu::OnMenuClick, this));
	this->exitLabel = new MenuLabel("Exit", Resources::Fonts_Marker_Felt, menuFontSize, CC_CALLBACK_1(OptionsMenu::OnMenuClick, this));

	this->mouse = new Mouse();
	this->clickableMenus = new vector<MenuLabel*>();

	this->titleLabel->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2 - this->titleLabel->getContentSize().height + menuOffset - spacing * 1.5));
	this->fullScreenLabel->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2 - this->fullScreenLabel->getContentSize().height / 2 + menuOffset + spacing * 0));
	this->windowedLabel->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2 - this->windowedLabel->getContentSize().height / 2 + menuOffset + spacing * 1));
	this->exitLabel->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2 - this->exitLabel->getContentSize().height / 2 + menuOffset + spacing * 2));
	this->background->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));

	this->clickableMenus->push_back(this->fullScreenLabel);
	this->clickableMenus->push_back(this->windowedLabel);
	this->clickableMenus->push_back(this->exitLabel);

	this->addChild(this->background);
	this->addChild(this->titleLabel);
	this->addChild(this->fullScreenLabel);
	this->addChild(this->windowedLabel);
	this->addChild(this->exitLabel);
	this->addChild(this->mouse);

	this->InitializeListeners();
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
}

void OptionsMenu::OnMenuClick(MenuLabel* menuLabel)
{
	if (menuLabel == fullScreenLabel)
	{
		ConfigManager::SetResolution(ConfigManager::ResolutionSetting::FullScreen);
	}
	else if (menuLabel == windowedLabel)
	{
		ConfigManager::SetResolution(ConfigManager::ResolutionSetting::R1080x768);
	}
}
