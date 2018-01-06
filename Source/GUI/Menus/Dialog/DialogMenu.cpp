#include "DialogMenu.h"

DialogMenu* DialogMenu::create(Dialog* dialogRoot)
{
	DialogMenu* dialogMenu = new DialogMenu(dialogRoot);

	dialogMenu->autorelease();

	return dialogMenu;
}

DialogMenu::DialogMenu(Dialog* dialogRoot)
{
	this->dialogMenu = Sprite::create(Resources::Menus_DialogMenu_DialogBox);
	this->dialog = Node::create();
	this->frameLeft = Sprite::create(Resources::Menus_DialogMenu_DialogFrameLeft);
	this->frameRight = Sprite::create(Resources::Menus_DialogMenu_DialogFrameRight);

	this->dialog->addChild(dialogRoot);

	this->addChild(this->dialogMenu);
	this->addChild(this->dialog);
	this->addChild(this->frameLeft);
	this->addChild(this->frameRight);
}

DialogMenu::~DialogMenu()
{
}

void DialogMenu::onEnter()
{
	Node::onEnter();

	this->initializePositions();
}

void DialogMenu::initializePositions()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->dialogMenu->setPosition(Vec2(visibleSize.width / 2.0f, this->dialogMenu->getContentSize().height / 2.0f + 16.0f));
	this->dialog->setPosition(Vec2(visibleSize.width / 2.0f, this->dialogMenu->getContentSize().height / 2));
	this->frameLeft->setPosition(Vec2(visibleSize.width / 2.0f - 732.0f, this->dialogMenu->getContentSize().height / 2.0f + 16.0f));
	this->frameRight->setPosition(Vec2(visibleSize.width / 2.0f + 732.0f, this->dialogMenu->getContentSize().height / 2.0f + 16.0f));
}
