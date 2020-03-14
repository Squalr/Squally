#include "WitchDoctorsWandPlans.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/ObjectResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string WitchDoctorsWandPlans::SaveKeyWitchDoctorsWandPlans = "witch-doctors-wand-plans";

WitchDoctorsWandPlans* WitchDoctorsWandPlans::create()
{
	WitchDoctorsWandPlans* instance = new WitchDoctorsWandPlans();

	instance->autorelease();

	return instance;
}

WitchDoctorsWandPlans::WitchDoctorsWandPlans() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}))
{
}

WitchDoctorsWandPlans::~WitchDoctorsWandPlans()
{
}

Item* WitchDoctorsWandPlans::craft()
{
	return WitchDoctorsWand::create();
}

std::vector<std::tuple<Item*, int>> WitchDoctorsWandPlans::getReagentsInternal()
{
	return
	{
		{ LightWood::create(), 6 },
		{ Gold::create(), 2 },
	};
}

Item* WitchDoctorsWandPlans::clone()
{
	return WitchDoctorsWandPlans::create();
}

std::string WitchDoctorsWandPlans::getItemName()
{
	return WitchDoctorsWandPlans::SaveKeyWitchDoctorsWandPlans;
}

LocalizedString* WitchDoctorsWandPlans::getString()
{
	return Strings::Items_Equipment_Weapons_Wands_WitchDoctorsWand::create();
}

std::string WitchDoctorsWandPlans::getIconResource()
{
	return ObjectResources::Items_Crafting_SCROLL_1;
}

std::string WitchDoctorsWandPlans::getCraftedItemIconResource()
{
	return ObjectResources::Items_Equipment_Weapons_Wands_WitchDoctorsWand;
}

std::string WitchDoctorsWandPlans::getSerializationKey()
{
	return WitchDoctorsWandPlans::SaveKeyWitchDoctorsWandPlans;
}
