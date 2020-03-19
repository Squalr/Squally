#include "Wood.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Wood::SaveKey = "wood";

Wood* Wood::create()
{
	Wood* instance = new Wood();

	instance->autorelease();

	return instance;
}

Wood::Wood() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 1 }}), ItemMeta(20000))
{
}

Wood::~Wood()
{
}

Item* Wood::clone()
{
	return Wood::create();
}

std::string Wood::getItemName()
{
	return Wood::SaveKey;
}

LocalizedString* Wood::getString()
{
	return Strings::Items_Crafting_Wood_Wood::create();
}

std::string Wood::getIconResource()
{
	return ItemResources::Crafting_Smithing_Wood;
}

std::string Wood::getSerializationKey()
{
	return Wood::SaveKey;
}
