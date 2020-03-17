#include "OldShoe.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string OldShoe::SaveKeyOldShoe = "old-shoe";

OldShoe* OldShoe::create()
{
	OldShoe* instance = new OldShoe();

	instance->autorelease();

	return instance;
}

OldShoe::OldShoe() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}), ItemStats(
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

OldShoe::~OldShoe()
{
}

Item* OldShoe::clone()
{
	return OldShoe::create();
}

std::string OldShoe::getItemName()
{
	return OldShoe::SaveKeyOldShoe;
}

LocalizedString* OldShoe::getString()
{
	return Strings::Items_Equipment_Gear_Hats_OldShoe::create();
}

std::string OldShoe::getIconResource()
{
	return ItemResources::Equipment_Gear_Hats_OldShoe;
}

std::string OldShoe::getSerializationKey()
{
	return OldShoe::SaveKeyOldShoe;
}

Vec2 OldShoe::getDisplayOffset()
{
	return Vec2(14.0f, 8.0f);
}
