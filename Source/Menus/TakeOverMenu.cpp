#include "TakeOverMenu.h"

TakeOverMenu * TakeOverMenu::create(Node* menu)
{
	TakeOverMenu* instance = new TakeOverMenu(menu);

	instance->autorelease();

	return instance;
}

TakeOverMenu::TakeOverMenu(Node* menu)
{
	this->menu = menu;
	this->background = Node::create();

	this->addChild(this->background);
	this->addChild(this->menu);

	this->setFadeSpeed(0.0f);
}

TakeOverMenu::~TakeOverMenu()
{
}

void TakeOverMenu::onEnter()
{
	SmartScene::onEnter();

	this->background->addChild(MenuBackground::claimInstance());
}

void TakeOverMenu::initializePositions()
{
	SmartScene::initializePositions();
}

void TakeOverMenu::initializeListeners()
{
	SmartScene::initializeListeners();
}
