#include "Gold.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Objects/Platformer/Collectables/IOU.h"

#include "Resources/ObjectResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Gold::SaveKeyGold = "gold";

Gold* Gold::create()
{
	Gold* instance = new Gold();

	instance->autorelease();

	return instance;
}

Gold::Gold() : super(CurrencyInventory::create({{ IOU::getIdentifier(), 1 }}), ItemMeta(20000))
{
}

Gold::~Gold()
{
}

Item* Gold::clone()
{
	return Gold::create();
}

std::string Gold::getItemName()
{
	return Gold::SaveKeyGold;
}

LocalizedString* Gold::getString()
{
	return Strings::Items_Crafting_Ore_Gold::create();
}

std::string Gold::getIconResource()
{
	return ObjectResources::Items_Reagents_Ores_Gold;
}

std::string Gold::getSerializationKey()
{
	return Gold::SaveKeyGold;
}
