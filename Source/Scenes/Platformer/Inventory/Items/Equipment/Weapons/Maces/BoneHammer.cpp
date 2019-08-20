#include "BoneHammer.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Objects/Platformer/Collectables/IOU.h"

#include "Resources/ObjectResources.h"

#include "Strings/Items/Equipment/Weapons/Maces/BoneHammer.h"

using namespace cocos2d;

const std::string BoneHammer::SaveKeyBoneHammer = "bone-hammer";

BoneHammer* BoneHammer::create()
{
	BoneHammer* instance = new BoneHammer();

	instance->autorelease();

	return instance;
}

BoneHammer::BoneHammer() : super(CurrencyInventory::create({{ IOU::getIdentifier(), 2 }}), 3, 6)
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
