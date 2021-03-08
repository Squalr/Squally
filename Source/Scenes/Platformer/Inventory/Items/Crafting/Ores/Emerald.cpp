#include "Emerald.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Emerald::SaveKey = "emerald";

Emerald* Emerald::create()
{
	Emerald* instance = new Emerald();

	instance->autorelease();

	return instance;
}

Emerald::Emerald() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 48 }}), ItemMeta(20000))
{
}

Emerald::~Emerald()
{
}

Item* Emerald::clone()
{
	return Emerald::create();
}

const std::string& Emerald::getItemName()
{
	return Emerald::SaveKey;
}

LocalizedString* Emerald::getString()
{
	return Strings::Items_Crafting_Ore_Emerald::create();
}

const std::string& Emerald::getIconResource()
{
	return ItemResources::Crafting_Smithing_Emerald;
}

const std::string& Emerald::getSerializationKey()
{
	return Emerald::SaveKey;
}
