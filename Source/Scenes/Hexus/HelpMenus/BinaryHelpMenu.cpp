#include "BinaryHelpMenu.h"

using namespace cocos2d;

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
	HelpMenuBase::onEnter();
}

void BinaryHelpMenu::initializePositions()
{
	HelpMenuBase::initializePositions();
}

void BinaryHelpMenu::initializeListeners()
{
	HelpMenuBase::initializeListeners();
}
