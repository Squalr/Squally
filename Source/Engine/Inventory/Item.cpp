#include "Item.h"

#include "cocos/base/CCValue.h"

#include "Engine/Localization/LocalizedString.h"

using namespace cocos2d;

const int Item::MaxStack = -1;

Item::Item(CurrencyInventory* cost, int stackSize)
{
	this->count = 1;
	this->stackSize = stackSize;
	this->cost = cost;
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

ValueMap Item::serialize()
{
	ValueMap result = ValueMap();

	return result;
}

int Item::getCount()
{
	return this->count;
}

int Item::getStackSize()
{
	return this->stackSize;
}
