#include "MenuBackground.h"

MenuBackground * MenuBackground::claimInstance()
{
	MenuBackground* menuBackground = new MenuBackground();

	menuBackground->autorelease();

	return menuBackground;
}

MenuBackground * MenuBackground::getInstance()
{
	MenuBackground* menuBackground = new MenuBackground();

	menuBackground->autorelease();

	return menuBackground;
}

MenuBackground::MenuBackground()
{
	this->background = Sprite::create(Resources::Menus_MenuBackground_Background);

	this->addChild(this->background);
}

MenuBackground::~MenuBackground()
{
}

void MenuBackground::onEnter()
{
	Node::onEnter();

	this->InitializePositions();
}

void MenuBackground::InitializePositions()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	this->background->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
}
