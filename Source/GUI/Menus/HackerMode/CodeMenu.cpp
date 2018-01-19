#include "CodeMenu.h"

CodeMenu* CodeMenu::create()
{
	CodeMenu* codeMenu = new CodeMenu();

	codeMenu->autorelease();

	return codeMenu;
}

CodeMenu::CodeMenu()
{
	this->codeMenuBackground = Sprite::create(Resources::Menus_HackerModeMenu_CodeMenu);
	this->closeButton = MenuSprite::create(Resources::Menus_HackerModeMenu_CloseButton, Resources::Menus_HackerModeMenu_CloseButtonHover, Resources::Menus_HackerModeMenu_CloseButtonClick);
	this->addChild(this->codeMenuBackground);
	this->addChild(this->closeButton);

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
	this->closeButton->setPosition(Vec2(visibleSize.width / 2.0f + 612.0f, visibleSize.height / 2.0f + 336.0f));
}

void CodeMenu::initializeListeners()
{
	this->closeButton->setClickCallback(CC_CALLBACK_1(CodeMenu::onClose, this));
}

void CodeMenu::onClose(MenuSprite* menuSprite)
{
	this->setVisible(false);

	Utils::focus(this->getParent());
}
