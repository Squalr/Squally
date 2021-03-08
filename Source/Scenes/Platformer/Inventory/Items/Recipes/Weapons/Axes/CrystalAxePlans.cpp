#include "CrystalAxePlans.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string CrystalAxePlans::SaveKey = "crystal-axe-plans";

CrystalAxePlans* CrystalAxePlans::create()
{
	CrystalAxePlans* instance = new CrystalAxePlans();

	instance->autorelease();

	return instance;
}

CrystalAxePlans::CrystalAxePlans() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}))
{
}

CrystalAxePlans::~CrystalAxePlans()
{
}

std::vector<Item*> CrystalAxePlans::craft()
{
	return { CrystalAxe::create() };
}

std::vector<std::tuple<Item*, int>> CrystalAxePlans::getReagentsInternal()
{
	return
	{
		{ Wood::create(), 2 },
		{ Iron::create(), 4 },
	};
}

Item* CrystalAxePlans::clone()
{
	return CrystalAxePlans::create();
}

const std::string& CrystalAxePlans::getItemName()
{
	return CrystalAxePlans::SaveKey;
}

LocalizedString* CrystalAxePlans::getString()
{
	return Strings::Items_Equipment_Weapons_Axes_CrystalAxe::create();
}

const std::string& CrystalAxePlans::getIconResource()
{
	return ItemResources::Misc_SCROLL_1;
}

std::string CrystalAxePlans::getCraftedItemIconResource()
{
	return ItemResources::Equipment_Weapons_Axes_CrystalAxe;
}

const std::string& CrystalAxePlans::getSerializationKey()
{
	return CrystalAxePlans::SaveKey;
}
