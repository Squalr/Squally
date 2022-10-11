#include "BrocksHelm.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string BrocksHelm::SaveKey = "brocks-helm";

BrocksHelm* BrocksHelm::create()
{
	BrocksHelm* instance = new BrocksHelm();

	instance->autorelease();

	return instance;
}

BrocksHelm::BrocksHelm() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}), ItemStats(
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

BrocksHelm::~BrocksHelm()
{
}

Item* BrocksHelm::clone()
{
	return BrocksHelm::create();
}

LocalizedString* BrocksHelm::getString()
{
	return Strings::Items_Equipment_Gear_Hats_BrocksHelm::create();
}

const std::string& BrocksHelm::getIconResource()
{
	return ItemResources::Equipment_Gear_Hats_BrocksHelm;
}

const std::string& BrocksHelm::getIdentifier()
{
	return BrocksHelm::SaveKey;
}

Vec2 BrocksHelm::getDisplayOffset()
{
	return Vec2(-6.0f, -20.0f);
}

Recipe* BrocksHelm::getRecipe()
{
	return nullptr;
}
