#include "CardPoolTutorial.h"

#include "cocos/base/CCValue.h"

#include "Scenes/Platformer/Inventory/Items/Collectables/HexusCards/HexusCards.h"

using namespace cocos2d;

CardPoolTutorial* CardPoolTutorial::create()
{
	CardPoolTutorial* instance = new CardPoolTutorial();

	instance->autorelease();

	return instance;
}

CardPoolTutorial::CardPoolTutorial() : super(ValueMap(), "card-pool-tutorial", 1, 2)
{
	this->addItemToPool(SpecialMov::create(), 1.00f);
}

CardPoolTutorial::~CardPoolTutorial()
{
}

void CardPoolTutorial::onEnter()
{
	super::onEnter(); 
}

void CardPoolTutorial::initializePositions()
{
	super::initializePositions();
}

void CardPoolTutorial::initializeListeners()
{
	super::initializeListeners();
}
