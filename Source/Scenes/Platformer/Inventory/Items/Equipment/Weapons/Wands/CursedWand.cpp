#include "CursedWand.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Objects/Platformer/Collectables/IOU.h"

#include "Resources/ObjectResources.h"

#include "Strings/Items/Equipment/Weapons/Wands/CursedWand.h"

using namespace cocos2d;

const std::string CursedWand::SaveKeyCursedWand = "cursed-wand";

CursedWand* CursedWand::create()
{
	CursedWand* instance = new CursedWand();

	instance->autorelease();

	return instance;
}

CursedWand::CursedWand() : super(CurrencyInventory::create({{ IOU::getIdentifier(), 2 }}), 3, 6)
{
}

CursedWand::~CursedWand()
{
}

Item* CursedWand::clone()
{
	return CursedWand::create();
}

std::string CursedWand::getItemName()
{
	return CursedWand::SaveKeyCursedWand;
}

LocalizedString* CursedWand::getString()
{
	return Strings::Items_Equipment_Weapons_Wands_CursedWand::create();
}

std::string CursedWand::getIconResource()
{
	return ObjectResources::Items_Equipment_Weapons_Wands_CursedWand;
}

std::string CursedWand::getSerializationKey()
{
	return CursedWand::SaveKeyCursedWand;
}

Vec2 CursedWand::getDisplayOffset()
{
	return Vec2(0.0f, -24.0f);
}
