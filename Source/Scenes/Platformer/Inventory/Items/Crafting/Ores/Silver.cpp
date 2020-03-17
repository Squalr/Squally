#include "Silver.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Silver::SaveKeySilver = "silver";

Silver* Silver::create()
{
	Silver* instance = new Silver();

	instance->autorelease();

	return instance;
}

Silver::Silver() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 1 }}), ItemMeta(20000))
{
}

Silver::~Silver()
{
}

Item* Silver::clone()
{
	return Silver::create();
}

std::string Silver::getItemName()
{
	return Silver::SaveKeySilver;
}

LocalizedString* Silver::getString()
{
	return Strings::Items_Crafting_Ore_Silver::create();
}

std::string Silver::getIconResource()
{
	return ItemResources::Crafting_Ores_Silver;
}

std::string Silver::getSerializationKey()
{
	return Silver::SaveKeySilver;
}
