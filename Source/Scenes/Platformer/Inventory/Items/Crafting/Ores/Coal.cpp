#include "Coal.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Coal::SaveKeyCoal = "coal";

Coal* Coal::create()
{
	Coal* instance = new Coal();

	instance->autorelease();

	return instance;
}

Coal::Coal() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 1 }}), ItemMeta(20000))
{
}

Coal::~Coal()
{
}

Item* Coal::clone()
{
	return Coal::create();
}

std::string Coal::getItemName()
{
	return Coal::SaveKeyCoal;
}

LocalizedString* Coal::getString()
{
	return Strings::Items_Crafting_Ore_Coal::create();
}

std::string Coal::getIconResource()
{
	return ItemResources::Crafting_Smithing_Coal;
}

std::string Coal::getSerializationKey()
{
	return Coal::SaveKeyCoal;
}
