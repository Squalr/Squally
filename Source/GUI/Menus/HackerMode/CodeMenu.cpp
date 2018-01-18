#include "CodeMenu.h"

CodeMenu* CodeMenu::create()
{
	CodeMenu* codeMenu = new CodeMenu();

	codeMenu->autorelease();

	return codeMenu;
}

CodeMenu::CodeMenu()
{
	this->codeMenuBackground = Sprite::create(Resources::Menus_HackerModeMenu_DataCodeMenu);

	this->addChild(this->codeMenuBackground);

	this->initializePositions();
	this->initializeListeners();
}

CodeMenu::~CodeMenu()
{
}

void CodeMenu::initializePositions()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->codeMenuBackground->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f));
}

void CodeMenu::initializeListeners()
{
}
