#include "RoyalCrown.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"

#include "Resources/ObjectResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string RoyalCrown::SaveKeyRoyalCrown = "royal-crown";

RoyalCrown* RoyalCrown::create()
{
	RoyalCrown* instance = new RoyalCrown();

	instance->autorelease();

	return instance;
}

RoyalCrown::RoyalCrown() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}), ItemStats(
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

RoyalCrown::~RoyalCrown()
{
}

Item* RoyalCrown::clone()
{
	return RoyalCrown::create();
}

std::string RoyalCrown::getItemName()
{
	return RoyalCrown::SaveKeyRoyalCrown;
}

LocalizedString* RoyalCrown::getString()
{
	return Strings::Items_Equipment_Gear_Hats_SantaHat::create();
}

std::string RoyalCrown::getIconResource()
{
	return ObjectResources::Items_Equipment_Gear_Hats_RoyalCrown;
}

std::string RoyalCrown::getSerializationKey()
{
	return RoyalCrown::SaveKeyRoyalCrown;
}

Vec2 RoyalCrown::getDisplayOffset()
{
	return Vec2(16.0f, -16.0f);
}
