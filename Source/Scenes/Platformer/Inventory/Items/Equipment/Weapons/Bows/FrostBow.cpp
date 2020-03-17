#include "FrostBow.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string FrostBow::SaveKeyFrostBow = "frost-bow";

FrostBow* FrostBow::create()
{
	FrostBow* instance = new FrostBow();

	instance->autorelease();

	return instance;
}

FrostBow::FrostBow() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}), 32, 40, ItemStats(
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

FrostBow::~FrostBow()
{
}

Item* FrostBow::clone()
{
	return FrostBow::create();
}

std::string FrostBow::getItemName()
{
	return FrostBow::SaveKeyFrostBow;
}

LocalizedString* FrostBow::getString()
{
	return Strings::Items_Equipment_Weapons_Bows_FrostBow::create();
}

std::string FrostBow::getIconResource()
{
	return ItemResources::Equipment_Weapons_Bows_FrostBow;
}

std::string FrostBow::getSerializationKey()
{
	return FrostBow::SaveKeyFrostBow;
}

Vec2 FrostBow::getDisplayOffset()
{
	return Vec2(0.0f, -24.0f);
}
