#include "Rune.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Rune::SaveKeyRune = "rune";

Rune* Rune::create()
{
	Rune* instance = new Rune();

	instance->autorelease();

	return instance;
}

Rune::Rune() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 1 }}), ItemMeta(20000))
{
}

Rune::~Rune()
{
}

Item* Rune::clone()
{
	return Rune::create();
}

std::string Rune::getItemName()
{
	return Rune::SaveKeyRune;
}

LocalizedString* Rune::getString()
{
	return Strings::Items_Crafting_Ore_Rune::create();
}

std::string Rune::getIconResource()
{
	return ItemResources::Crafting_Smithing_Rune;
}

std::string Rune::getSerializationKey()
{
	return Rune::SaveKeyRune;
}
