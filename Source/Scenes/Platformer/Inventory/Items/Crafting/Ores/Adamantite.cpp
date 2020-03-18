#include "Adamantite.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Adamantite::SaveKeyAdamantite = "adamantite";

Adamantite* Adamantite::create()
{
	Adamantite* instance = new Adamantite();

	instance->autorelease();

	return instance;
}

Adamantite::Adamantite() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 1 }}), ItemMeta(20000))
{
}

Adamantite::~Adamantite()
{
}

Item* Adamantite::clone()
{
	return Adamantite::create();
}

std::string Adamantite::getItemName()
{
	return Adamantite::SaveKeyAdamantite;
}

LocalizedString* Adamantite::getString()
{
	return Strings::Items_Crafting_Ore_Adamantite::create();
}

std::string Adamantite::getIconResource()
{
	return ItemResources::Crafting_Smithing_Adamantite;
}

std::string Adamantite::getSerializationKey()
{
	return Adamantite::SaveKeyAdamantite;
}
