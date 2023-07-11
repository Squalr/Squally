#include "Silver.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Silver::SaveKey = "silver";

Silver* Silver::create()
{
	Silver* instance = new Silver();

	instance->autorelease();

	return instance;
}

Silver::Silver() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 12 * 2 }}), ItemMeta(20000))
{
}

Silver::~Silver()
{
}

Item* Silver::clone()
{
	return Silver::create();
}

LocalizedString* Silver::getString()
{
	return Strings::Items_Crafting_Ore_Silver::create();
}

const std::string& Silver::getIconResource()
{
	return ItemResources::Crafting_Smithing_T2_Silver;
}

const std::string& Silver::getIdentifier()
{
	return Silver::SaveKey;
}
