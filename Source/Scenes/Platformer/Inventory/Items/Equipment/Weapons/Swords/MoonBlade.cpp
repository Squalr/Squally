#include "MoonBlade.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string MoonBlade::SaveKeyMoonBlade = "moon-blade";

MoonBlade* MoonBlade::create()
{
	MoonBlade* instance = new MoonBlade();

	instance->autorelease();

	return instance;
}

MoonBlade::MoonBlade() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}), 16, 24, ItemStats(
	// Health
	0,
	// Mana
	0,
	// Attack
	0,
	// Armor
	0,
	// Speed
	0.05f
))
{
}

MoonBlade::~MoonBlade()
{
}

Item* MoonBlade::clone()
{
	return MoonBlade::create();
}

std::string MoonBlade::getItemName()
{
	return MoonBlade::SaveKeyMoonBlade;
}

LocalizedString* MoonBlade::getString()
{
	return Strings::Items_Equipment_Weapons_Swords_MoonBlade::create();
}

std::string MoonBlade::getIconResource()
{
	return ItemResources::Equipment_Weapons_Swords_MoonBlade;
}

std::string MoonBlade::getSerializationKey()
{
	return MoonBlade::SaveKeyMoonBlade;
}
