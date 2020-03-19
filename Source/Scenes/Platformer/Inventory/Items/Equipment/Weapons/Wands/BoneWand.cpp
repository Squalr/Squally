#include "BoneWand.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string BoneWand::SaveKey = "bone-wand";

BoneWand* BoneWand::create()
{
	BoneWand* instance = new BoneWand();

	instance->autorelease();

	return instance;
}

BoneWand::BoneWand() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}), 16, 20, ItemStats(
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

BoneWand::~BoneWand()
{
}

Item* BoneWand::clone()
{
	return BoneWand::create();
}

std::string BoneWand::getItemName()
{
	return BoneWand::SaveKey;
}

LocalizedString* BoneWand::getString()
{
	return Strings::Items_Equipment_Weapons_Wands_BoneWand::create();
}

std::string BoneWand::getIconResource()
{
	return ItemResources::Equipment_Weapons_Wands_BoneWand;
}

std::string BoneWand::getSerializationKey()
{
	return BoneWand::SaveKey;
}

Vec2 BoneWand::getDisplayOffset()
{
	return Vec2(0.0f, -24.0f);
}
