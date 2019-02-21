#include "Item.h"

#include "Engine/Localization/LocalizedString.h"

using namespace cocos2d;

Item::Item(LocalizedString* name, std::string iconResource)
{
	this->name = name;
	this->iconResource = iconResource;

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

std::string Item::getIconResource()
{
	return this->iconResource;
}