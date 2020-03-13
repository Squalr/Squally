#include "SteelAxePlans.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/ObjectResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string SteelAxePlans::SaveKeySteelAxePlans = "steel-axe-plans";

SteelAxePlans* SteelAxePlans::create()
{
	SteelAxePlans* instance = new SteelAxePlans();

	instance->autorelease();

	return instance;
}

SteelAxePlans::SteelAxePlans() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}))
{
}

SteelAxePlans::~SteelAxePlans()
{
}

Item* SteelAxePlans::craft()
{
	return SteelAxe::create();
}

std::map<Item*, int> SteelAxePlans::getReagentsInternal()
{
	return
	{
		{ Wood::create(), 2 },
		{ Iron::create(), 4 },
	};
}

Item* SteelAxePlans::clone()
{
	return SteelAxePlans::create();
}

std::string SteelAxePlans::getItemName()
{
	return SteelAxePlans::SaveKeySteelAxePlans;
}

LocalizedString* SteelAxePlans::getString()
{
	return Strings::Items_Equipment_Weapons_Axes_SteelAxe::create();
}

std::string SteelAxePlans::getIconResource()
{
	return ObjectResources::Items_Crafting_SCROLL_1;
}

std::string SteelAxePlans::getCraftedItemIconResource()
{
	return ObjectResources::Items_Equipment_Weapons_Axes_SteelAxe;
}

std::string SteelAxePlans::getSerializationKey()
{
	return SteelAxePlans::SaveKeySteelAxePlans;
}
