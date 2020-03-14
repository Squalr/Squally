#include "OlympusBowPlans.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/ObjectResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string OlympusBowPlans::SaveKeyOlympusBowPlans = "olympus-bow-plans";

OlympusBowPlans* OlympusBowPlans::create()
{
	OlympusBowPlans* instance = new OlympusBowPlans();

	instance->autorelease();

	return instance;
}

OlympusBowPlans::OlympusBowPlans() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}))
{
}

OlympusBowPlans::~OlympusBowPlans()
{
}

Item* OlympusBowPlans::craft()
{
	return OlympusBow::create();
}

std::vector<std::tuple<Item*, int>> OlympusBowPlans::getReagentsInternal()
{
	return
	{
		{ Wood::create(), 6 },
		{ Iron::create(), 4 },
		{ Coal::create(), 4 },
		{ Gold::create(), 4 },
	};
}

Item* OlympusBowPlans::clone()
{
	return OlympusBowPlans::create();
}

std::string OlympusBowPlans::getItemName()
{
	return OlympusBowPlans::SaveKeyOlympusBowPlans;
}

LocalizedString* OlympusBowPlans::getString()
{
	return Strings::Items_Equipment_Weapons_Bows_OlympusBow::create();
}

std::string OlympusBowPlans::getIconResource()
{
	return ObjectResources::Items_Crafting_SCROLL_1;
}

std::string OlympusBowPlans::getCraftedItemIconResource()
{
	return ObjectResources::Items_Equipment_Weapons_Bows_OlympusBow;
}

std::string OlympusBowPlans::getSerializationKey()
{
	return OlympusBowPlans::SaveKeyOlympusBowPlans;
}
