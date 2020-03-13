#include "RapierPlans.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/ObjectResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string RapierPlans::SaveKeyRapierPlans = "rapier-plans";

RapierPlans* RapierPlans::create()
{
	RapierPlans* instance = new RapierPlans();

	instance->autorelease();

	return instance;
}

RapierPlans::RapierPlans() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}))
{
}

RapierPlans::~RapierPlans()
{
}

Item* RapierPlans::craft()
{
	return Rapier::create();
}

std::map<Item*, int> RapierPlans::getReagentsInternal()
{
	return
	{
		{ Wood::create(), 2 },
		{ Iron::create(), 4 },
	};
}

Item* RapierPlans::clone()
{
	return RapierPlans::create();
}

std::string RapierPlans::getItemName()
{
	return RapierPlans::SaveKeyRapierPlans;
}

LocalizedString* RapierPlans::getString()
{
	return Strings::Items_Equipment_Weapons_Swords_Rapier::create();
}

std::string RapierPlans::getIconResource()
{
	return ObjectResources::Items_Crafting_SCROLL_1;
}

std::string RapierPlans::getCraftedItemIconResource()
{
	return ObjectResources::Items_Equipment_Weapons_Swords_Rapier;
}

std::string RapierPlans::getSerializationKey()
{
	return RapierPlans::SaveKeyRapierPlans;
}
