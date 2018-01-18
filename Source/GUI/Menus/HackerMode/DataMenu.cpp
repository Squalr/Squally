#include "DataMenu.h"

DataMenu* DataMenu::create()
{
	DataMenu* dataMenu = new DataMenu();

	dataMenu->autorelease();

	return dataMenu;
}

DataMenu::DataMenu()
{
	this->dataMenuBackground = Sprite::create(Resources::Menus_HackerModeMenu_DataCodeMenu);

	this->addChild(this->dataMenuBackground);

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
}

void DataMenu::initializeListeners()
{
}
