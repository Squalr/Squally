#include "CrossBowPlans.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/ObjectResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string CrossBowPlans::SaveKeyCrossBowPlans = "cross-bow-plans";

CrossBowPlans* CrossBowPlans::create()
{
	CrossBowPlans* instance = new CrossBowPlans();

	instance->autorelease();

	return instance;
}

CrossBowPlans::CrossBowPlans() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}))
{
}

CrossBowPlans::~CrossBowPlans()
{
}

Item* CrossBowPlans::craft()
{
	return CrossBow::create();
}

std::vector<std::tuple<Item*, int>> CrossBowPlans::getReagentsInternal()
{
	return
	{
		{ LightWood::create(), 8 },
		{ Iron::create(), 2 },
	};
}

Item* CrossBowPlans::clone()
{
	return CrossBowPlans::create();
}

std::string CrossBowPlans::getItemName()
{
	return CrossBowPlans::SaveKeyCrossBowPlans;
}

LocalizedString* CrossBowPlans::getString()
{
	return Strings::Items_Equipment_Weapons_Bows_CrossBow::create();
}

std::string CrossBowPlans::getIconResource()
{
	return ObjectResources::Items_Crafting_SCROLL_1;
}

std::string CrossBowPlans::getCraftedItemIconResource()
{
	return ObjectResources::Items_Equipment_Weapons_Bows_CrossBow;
}

std::string CrossBowPlans::getSerializationKey()
{
	return CrossBowPlans::SaveKeyCrossBowPlans;
}
