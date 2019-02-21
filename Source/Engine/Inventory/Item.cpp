#include "Item.h"

#include "Engine/Localization/LocalizedString.h"

using namespace cocos2d;

Item::Item(LocalizedString* name)
{
	this->name = name;

	this->addChild(this->name);
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

LocalizedString* Item::cloneName()
{
	return this->name == nullptr ? nullptr : this->name->clone();
}