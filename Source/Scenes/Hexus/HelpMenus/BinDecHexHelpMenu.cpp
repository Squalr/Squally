#include "BinDecHexHelpMenu.h"

using namespace cocos2d;

BinDecHexHelpMenu* BinDecHexHelpMenu::create()
{
	BinDecHexHelpMenu* instance = new BinDecHexHelpMenu();

	instance->autorelease();

	return instance;
}

BinDecHexHelpMenu::BinDecHexHelpMenu()
{
}

BinDecHexHelpMenu::~BinDecHexHelpMenu()
{
}

void BinDecHexHelpMenu::onEnter()
{
	HelpMenuBase::onEnter();
}

void BinDecHexHelpMenu::initializePositions()
{
	HelpMenuBase::initializePositions();
}

void BinDecHexHelpMenu::initializeListeners()
{
	HelpMenuBase::initializeListeners();
}
