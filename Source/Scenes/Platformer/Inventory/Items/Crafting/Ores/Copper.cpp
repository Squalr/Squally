#include "Copper.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Objects/Platformer/Collectables/IOU.h"

#include "Resources/ObjectResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Copper::SaveKeyCopper = "copper";

Copper* Copper::create()
{
	Copper* instance = new Copper();

	instance->autorelease();

	return instance;
}

Copper::Copper() : super(CurrencyInventory::create({{ IOU::getIdentifier(), 1 }}), ItemMeta(20000))
{
}

Copper::~Copper()
{
}

Item* Copper::clone()
{
	return Copper::create();
}

std::string Copper::getItemName()
{
	return Copper::SaveKeyCopper;
}

LocalizedString* Copper::getString()
{
	return Strings::Items_Crafting_Ore_Copper::create();
}

std::string Copper::getIconResource()
{
	return ObjectResources::Items_Reagents_Ores_Copper;
}

std::string Copper::getSerializationKey()
{
	return Copper::SaveKeyCopper;
}
