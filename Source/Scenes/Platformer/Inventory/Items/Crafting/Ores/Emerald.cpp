#include "Emerald.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Objects/Platformer/Collectables/IOU.h"

#include "Resources/ObjectResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Emerald::SaveKeyEmerald = "emerald";

Emerald* Emerald::create()
{
	Emerald* instance = new Emerald();

	instance->autorelease();

	return instance;
}

Emerald::Emerald() : super(CurrencyInventory::create({{ IOU::getIdentifier(), 1 }}))
{
}

Emerald::~Emerald()
{
}

Item* Emerald::clone()
{
	return Emerald::create();
}

std::string Emerald::getItemName()
{
	return Emerald::SaveKeyEmerald;
}

LocalizedString* Emerald::getString()
{
	return Strings::Items_Crafting_Ore_Emerald::create();
}

std::string Emerald::getIconResource()
{
	return ObjectResources::Items_Reagents_Ores_Emerald;
}

std::string Emerald::getSerializationKey()
{
	return Emerald::SaveKeyEmerald;
}
