#include "RoyalCrown.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string RoyalCrown::SaveKey = "royal-crown";

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
	// Magic Attack
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

LocalizedString* RoyalCrown::getString()
{
	return Strings::Items_Equipment_Gear_Hats_RoyalCrown::create();
}

const std::string& RoyalCrown::getIconResource()
{
	return ItemResources::Equipment_Gear_Hats_RoyalCrown;
}

const std::string& RoyalCrown::getIdentifier()
{
	return RoyalCrown::SaveKey;
}

Vec2 RoyalCrown::getDisplayOffset()
{
	return Vec2(16.0f, -16.0f);
}
