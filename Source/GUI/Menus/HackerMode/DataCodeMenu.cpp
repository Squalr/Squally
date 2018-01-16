#include "DataCodeMenu.h"

DataCodeMenu* DataCodeMenu::create()
{
	DataCodeMenu* dataCodeMenu = new DataCodeMenu();

	dataCodeMenu->autorelease();

	return dataCodeMenu;
}

DataCodeMenu::DataCodeMenu()
{
	this->menuBackground = Sprite::create(Resources::Menus_HackerModeMenu_DataCodeMenu);
	this->closeButton = MenuSprite::create(Resources::Menus_Buttons_CloseButtonGreen, Resources::Menus_Buttons_CloseButtonGreenHover, Resources::Menus_Buttons_CloseButtonGreenClick);

	this->addChild(this->menuBackground);
	this->addChild(this->closeButton);

	this->initializePositions();
	this->initializeListeners();
}

DataCodeMenu::~DataCodeMenu()
{
}

void DataCodeMenu::activate()
{
	this->setVisible(true);

	Utils::resume(this);
}

void DataCodeMenu::initializePositions()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->menuBackground->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f));
	this->closeButton->setPosition(Vec2(visibleSize.width / 2.0f + 604.0f, visibleSize.height / 2.0f + 336.0f));
}

void DataCodeMenu::initializeListeners()
{
	this->closeButton->setClickCallback(CC_CALLBACK_1(DataCodeMenu::onClose, this));
}

void DataCodeMenu::onClose(MenuSprite* menuSprite)
{
	this->setVisible(false);

	Utils::resume(Director::getInstance()->getRunningScene());
}
