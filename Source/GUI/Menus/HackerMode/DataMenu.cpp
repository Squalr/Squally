#include "DataMenu.h"

DataMenu* DataMenu::create()
{
	DataMenu* dataMenu = new DataMenu();

	dataMenu->autorelease();

	return dataMenu;
}

DataMenu::DataMenu()
{
	this->dataMenuBackground = Sprite::create(Resources::Menus_HackerModeMenu_DataMenu);
	this->closeButton = MenuSprite::create(Resources::Menus_HackerModeMenu_CloseButton, Resources::Menus_HackerModeMenu_CloseButtonHover, Resources::Menus_HackerModeMenu_CloseButtonClick);

	this->addChild(this->dataMenuBackground);
	this->addChild(this->closeButton);

	this->initializePositions();
	this->initializeListeners();
}

DataMenu::~DataMenu()
{
}

void DataMenu::initializePositions()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->dataMenuBackground->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f));
	this->closeButton->setPosition(Vec2(visibleSize.width / 2.0f + 612.0f, visibleSize.height / 2.0f + 336.0f));
}

void DataMenu::initializeListeners()
{
	this->closeButton->setClickCallback(CC_CALLBACK_1(DataMenu::onClose, this));
}

void DataMenu::onClose(MenuSprite* menuSprite)
{
	this->setVisible(false);

	Utils::focus(this->getParent());
}
