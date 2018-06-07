#include "BinaryHelpMenu.h"

BinaryHelpMenu* BinaryHelpMenu::create()
{
	BinaryHelpMenu* binaryHelpMenu = new BinaryHelpMenu();

	binaryHelpMenu->autorelease();

	return binaryHelpMenu;
}

BinaryHelpMenu::BinaryHelpMenu()
{
}

BinaryHelpMenu::~BinaryHelpMenu()
{
}

void BinaryHelpMenu::onEnter()
{
	BinaryHelpMenu::onEnter();

	this->initializePositions();
	this->initializeListeners();
}

void BinaryHelpMenu::initializePositions()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
}

void BinaryHelpMenu::initializeListeners()
{
}
