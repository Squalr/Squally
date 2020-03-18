#include "VoidWandPlans.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string VoidWandPlans::SaveKeyVoidWandPlans = "void-wand-plans";

VoidWandPlans* VoidWandPlans::create()
{
	VoidWandPlans* instance = new VoidWandPlans();

	instance->autorelease();

	return instance;
}

VoidWandPlans::VoidWandPlans() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}))
{
}

VoidWandPlans::~VoidWandPlans()
{
}

Item* VoidWandPlans::craft()
{
	return WitchDoctorsWand::create();
}

std::vector<std::tuple<Item*, int>> VoidWandPlans::getReagentsInternal()
{
	return
	{
		{ LightWood::create(), 6 },
		{ Gold::create(), 2 },
	};
}

Item* VoidWandPlans::clone()
{
	return VoidWandPlans::create();
}

std::string VoidWandPlans::getItemName()
{
	return VoidWandPlans::SaveKeyVoidWandPlans;
}

LocalizedString* VoidWandPlans::getString()
{
	return Strings::Items_Equipment_Weapons_Wands_WitchDoctorsWand::create();
}

std::string VoidWandPlans::getIconResource()
{
	return ItemResources::Misc_SCROLL_1;
}

std::string VoidWandPlans::getCraftedItemIconResource()
{
	return ItemResources::Equipment_Weapons_Wands_WitchDoctorsWand;
}

std::string VoidWandPlans::getSerializationKey()
{
	return VoidWandPlans::SaveKeyVoidWandPlans;
}
