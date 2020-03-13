#include "CrystalMacePlans.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/ObjectResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string CrystalMacePlans::SaveKeyCrystalMacePlans = "crystal-mace-plans";

CrystalMacePlans* CrystalMacePlans::create()
{
	CrystalMacePlans* instance = new CrystalMacePlans();

	instance->autorelease();

	return instance;
}

CrystalMacePlans::CrystalMacePlans() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}))
{
}

CrystalMacePlans::~CrystalMacePlans()
{
}

Item* CrystalMacePlans::craft()
{
	return CrystalMace::create();
}

std::map<Item*, int> CrystalMacePlans::getReagentsInternal()
{
	return
	{
		{ Wood::create(), 2 },
		{ Iron::create(), 4 },
	};
}

Item* CrystalMacePlans::clone()
{
	return CrystalMacePlans::create();
}

std::string CrystalMacePlans::getItemName()
{
	return CrystalMacePlans::SaveKeyCrystalMacePlans;
}

LocalizedString* CrystalMacePlans::getString()
{
	return Strings::Items_Equipment_Weapons_Maces_CrystalMace::create();
}

std::string CrystalMacePlans::getIconResource()
{
	return ObjectResources::Items_Crafting_SCROLL_1;
}

std::string CrystalMacePlans::getCraftedItemIconResource()
{
	return ObjectResources::Items_Equipment_Weapons_Maces_CrystalMace;
}

std::string CrystalMacePlans::getSerializationKey()
{
	return CrystalMacePlans::SaveKeyCrystalMacePlans;
}
