#include "Item.h"

#include "cocos/base/CCValue.h"

#include "Engine/Localization/LocalizedString.h"

using namespace cocos2d;

Item::Item()
{
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

cocos2d::ValueMap Item::serialize()
{
	ValueMap result = ValueMap();

	return result;
}
