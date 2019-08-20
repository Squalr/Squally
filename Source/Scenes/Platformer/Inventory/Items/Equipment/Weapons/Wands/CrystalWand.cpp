#include "CrystalWand.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Objects/Platformer/Collectables/IOU.h"

#include "Resources/ObjectResources.h"

#include "Strings/Items/Equipment/Weapons/Wands/CrystalWand.h"

using namespace cocos2d;

const std::string CrystalWand::SaveKeyCrystalWand = "crystal-wand";

CrystalWand* CrystalWand::create()
{
	CrystalWand* instance = new CrystalWand();

	instance->autorelease();

	return instance;
}

CrystalWand::CrystalWand() : super(CurrencyInventory::create({{ IOU::getIdentifier(), 2 }}), 3, 6)
{
}

CrystalWand::~CrystalWand()
{
}

Item* CrystalWand::clone()
{
	return CrystalWand::create();
}

std::string CrystalWand::getItemName()
{
	return CrystalWand::SaveKeyCrystalWand;
}

LocalizedString* CrystalWand::getString()
{
	return Strings::Items_Equipment_Weapons_Wands_CrystalWand::create();
}

std::string CrystalWand::getIconResource()
{
	return ObjectResources::Items_Equipment_Weapons_Wands_CrystalWand;
}

std::string CrystalWand::getSerializationKey()
{
	return CrystalWand::SaveKeyCrystalWand;
}

Vec2 CrystalWand::getDisplayOffset()
{
	return Vec2(0.0f, -24.0f);
}
