#include "Sapphire.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Sapphire::SaveKey = "sapphire";

Sapphire* Sapphire::create()
{
	Sapphire* instance = new Sapphire();

	instance->autorelease();

	return instance;
}

Sapphire::Sapphire() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 1 }}), ItemMeta(20000))
{
}

Sapphire::~Sapphire()
{
}

Item* Sapphire::clone()
{
	return Sapphire::create();
}

std::string Sapphire::getItemName()
{
	return Sapphire::SaveKey;
}

LocalizedString* Sapphire::getString()
{
	return Strings::Items_Crafting_Ore_Sapphire::create();
}

std::string Sapphire::getIconResource()
{
	return ItemResources::Crafting_Smithing_Sapphire;
}

std::string Sapphire::getSerializationKey()
{
	return Sapphire::SaveKey;
}
