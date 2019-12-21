#include "HolyWand.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Objects/Platformer/Collectables/IOU.h"

#include "Resources/ObjectResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string HolyWand::SaveKeyHolyWand = "holy-wand";

HolyWand* HolyWand::create()
{
	HolyWand* instance = new HolyWand();

	instance->autorelease();

	return instance;
}

HolyWand::HolyWand() : super(CurrencyInventory::create({{ IOU::getIdentifier(), 2 }}), 3, 6, ItemStats(
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

HolyWand::~HolyWand()
{
}

Item* HolyWand::clone()
{
	return HolyWand::create();
}

std::string HolyWand::getItemName()
{
	return HolyWand::SaveKeyHolyWand;
}

LocalizedString* HolyWand::getString()
{
	return Strings::Items_Equipment_Weapons_Wands_HolyWand::create();
}

std::string HolyWand::getIconResource()
{
	return ObjectResources::Items_Equipment_Weapons_Wands_HolyWand;
}

std::string HolyWand::getSerializationKey()
{
	return HolyWand::SaveKeyHolyWand;
}

Vec2 HolyWand::getDisplayOffset()
{
	return Vec2(0.0f, -24.0f);
}
