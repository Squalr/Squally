#include "UnstableElement.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string UnstableElement::SaveKey = "unstable-element";

UnstableElement* UnstableElement::create()
{
	UnstableElement* instance = new UnstableElement();

	instance->autorelease();

	return instance;
}

UnstableElement::UnstableElement() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 1 }}), ItemMeta(1, 1))
{
}

UnstableElement::~UnstableElement()
{
}

Item* UnstableElement::clone()
{
	return UnstableElement::create();
}

LocalizedString* UnstableElement::getString()
{
	return Strings::Items_Misc_Keys_UnstableElement::create();
}

const std::string& UnstableElement::getIconResource()
{
	return ItemResources::Misc_UnstableElement;
}

const std::string& UnstableElement::getIdentifier()
{
	return UnstableElement::SaveKey;
}

