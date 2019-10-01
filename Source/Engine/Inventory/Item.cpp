#include "Item.h"

#include "cocos/base/CCValue.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Engine/Localization/LocalizedString.h"

using namespace cocos2d;

const int Item::MaxStack = -1;

Item::Item(CurrencyInventory* cost, int stackSize)
{
	this->count = 1;
	this->stackSize = stackSize;
	this->cost = cost;

	this->addChild(this->cost);
}

Item::~Item()
{
}

void Item::onEnter()
{
	super::onEnter();
}

void Item::initializeListeners()
{
	super::initializeListeners();
}

int Item::getCount()
{
	return this->count;
}

int Item::getStackSize()
{
	return this->stackSize;
}

CurrencyInventory* Item::getCost()
{
	return this->cost;
}
