#include "Item.h"

#include "cocos/base/CCValue.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Engine/Utils/MathUtils.h"

using namespace cocos2d;

Item::Item(CurrencyInventory* cost, ItemMeta itemMeta)
{
	this->cost = cost;
	this->itemMeta = itemMeta;

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

CurrencyInventory* Item::getCost()
{
	return this->cost;
}

int Item::getStackSize()
{
	return this->itemMeta.stackSize;
}

int Item::getUniqueCount()
{
	return this->itemMeta.unique;
}

int Item::getRubberBand()
{
	return this->itemMeta.rubberBanding.rubberBand;
}

float Item::getRubberBandFactor()
{
	return MathUtils::clamp(this->itemMeta.rubberBanding.rubberBandFactor, 0.0f, 1.0f);
}
