#include "BoneBow.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Objects/Platformer/Collectables/IOU.h"

#include "Resources/ObjectResources.h"

#include "Strings/Items/Equipment/Weapons/Bows/BoneBow.h"

using namespace cocos2d;

const std::string BoneBow::SaveKeyBoneBow = "bone-bow";

BoneBow* BoneBow::create()
{
	BoneBow* instance = new BoneBow();

	instance->autorelease();

	return instance;
}

BoneBow::BoneBow() : super(CurrencyInventory::create({{ IOU::getIdentifier(), 2 }}), 3, 6)
{
}

BoneBow::~BoneBow()
{
}

Item* BoneBow::clone()
{
	return BoneBow::create();
}

std::string BoneBow::getItemName()
{
	return BoneBow::SaveKeyBoneBow;
}

LocalizedString* BoneBow::getString()
{
	return Strings::Items_Equipment_Weapons_Bows_BoneBow::create();
}

std::string BoneBow::getIconResource()
{
	return ObjectResources::Items_Equipment_Weapons_Bows_BoneBow;
}

std::string BoneBow::getSerializationKey()
{
	return BoneBow::SaveKeyBoneBow;
}

Vec2 BoneBow::getDisplayOffset()
{
	return Vec2(0.0f, -24.0f);
}
