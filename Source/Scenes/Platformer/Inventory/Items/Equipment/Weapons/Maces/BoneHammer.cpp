#include "BoneHammer.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Objects/Platformer/Collectables/IOU.h"

#include "Resources/ObjectResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string BoneHammer::SaveKeyBoneHammer = "bone-hammer";

BoneHammer* BoneHammer::create()
{
	BoneHammer* instance = new BoneHammer();

	instance->autorelease();

	return instance;
}

BoneHammer::BoneHammer() : super(CurrencyInventory::create({{ IOU::getIdentifier(), 2 }}), 3, 6, ItemStats(
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

BoneHammer::~BoneHammer()
{
}

Item* BoneHammer::clone()
{
	return BoneHammer::create();
}

std::string BoneHammer::getItemName()
{
	return BoneHammer::SaveKeyBoneHammer;
}

LocalizedString* BoneHammer::getString()
{
	return Strings::Items_Equipment_Weapons_Maces_BoneHammer::create();
}

std::string BoneHammer::getIconResource()
{
	return ObjectResources::Items_Equipment_Weapons_Maces_BoneHammer;
}

std::string BoneHammer::getSerializationKey()
{
	return BoneHammer::SaveKeyBoneHammer;
}

Vec2 BoneHammer::getDisplayOffset()
{
	return Vec2(0.0f, -24.0f);
}
