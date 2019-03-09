#include "Item.h"

#include "cocos/base/CCValue.h"

#include "Engine/Localization/LocalizedString.h"

using namespace cocos2d;

Item::Item(int stackSize)
{
	this->count = 1;
	this->stackSize = stackSize;
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
