#include "CrystalMacePlans.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string CrystalMacePlans::SaveKey = "crystal-mace-plans";

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

std::vector<Item*> CrystalMacePlans::craft()
{
	return { CrystalMace::create() };
}

std::vector<std::tuple<Item*, int>> CrystalMacePlans::getReagentsInternal()
{
	return
	{
		{ Iron::create(), 6 },
		{ Coal::create(), 4 },
		{ Gold::create(), 4 },
		{ Diamond::create(), 8 },
	};
}

Item* CrystalMacePlans::clone()
{
	return CrystalMacePlans::create();
}

LocalizedString* CrystalMacePlans::getString()
{
	return Strings::Items_Equipment_Weapons_Maces_CrystalMace::create();
}

const std::string& CrystalMacePlans::getIconResource()
{
	return ItemResources::Misc_SCROLL_1;
}

std::string CrystalMacePlans::getCraftedItemIconResource()
{
	return ItemResources::Equipment_Weapons_Maces_CrystalMace;
}

const std::string& CrystalMacePlans::getIdentifier()
{
	return CrystalMacePlans::SaveKey;
}
