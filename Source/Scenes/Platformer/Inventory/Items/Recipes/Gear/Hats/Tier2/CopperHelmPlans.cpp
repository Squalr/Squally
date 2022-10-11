#include "CopperHelmPlans.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string CopperHelmPlans::SaveKey = "copper-helm-plans";

CopperHelmPlans* CopperHelmPlans::create()
{
	CopperHelmPlans* instance = new CopperHelmPlans();

	instance->autorelease();

	return instance;
}

CopperHelmPlans::CopperHelmPlans() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}))
{
}

CopperHelmPlans::~CopperHelmPlans()
{
}

std::vector<Item*> CopperHelmPlans::craft()
{
	return { CopperHelm::create() };
}

std::vector<std::tuple<Item*, int>> CopperHelmPlans::getReagentsInternal()
{
	return
	{
		{ Wood::create(), 2 },
		{ Iron::create(), 4 },
	};
}

Item* CopperHelmPlans::clone()
{
	return CopperHelmPlans::create();
}

LocalizedString* CopperHelmPlans::getString()
{
	return Strings::Items_Equipment_Gear_Hats_CopperHelm::create();
}

const std::string& CopperHelmPlans::getIconResource()
{
	return ItemResources::Misc_SCROLL_1;
}

std::string CopperHelmPlans::getCraftedItemIconResource()
{
	return ItemResources::Equipment_Gear_Hats_CopperHelm;
}

const std::string& CopperHelmPlans::getIdentifier()
{
	return CopperHelmPlans::SaveKey;
}
