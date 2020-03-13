#include "SkullCrusherPlans.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/ObjectResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string SkullCrusherPlans::SaveKeySkullCrusherPlans = "skull-crusher-plans";

SkullCrusherPlans* SkullCrusherPlans::create()
{
	SkullCrusherPlans* instance = new SkullCrusherPlans();

	instance->autorelease();

	return instance;
}

SkullCrusherPlans::SkullCrusherPlans() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}))
{
}

SkullCrusherPlans::~SkullCrusherPlans()
{
}

Item* SkullCrusherPlans::craft()
{
	return SkullCrusher::create();
}

std::map<Item*, int> SkullCrusherPlans::getReagentsInternal()
{
	return
	{
		{ Wood::create(), 2 },
		{ Iron::create(), 4 },
	};
}

Item* SkullCrusherPlans::clone()
{
	return SkullCrusherPlans::create();
}

std::string SkullCrusherPlans::getItemName()
{
	return SkullCrusherPlans::SaveKeySkullCrusherPlans;
}

LocalizedString* SkullCrusherPlans::getString()
{
	return Strings::Items_Equipment_Weapons_Maces_SkullCrusher::create();
}

std::string SkullCrusherPlans::getIconResource()
{
	return ObjectResources::Items_Crafting_SCROLL_1;
}

std::string SkullCrusherPlans::getCraftedItemIconResource()
{
	return ObjectResources::Items_Equipment_Weapons_Maces_SkullCrusher;
}

std::string SkullCrusherPlans::getSerializationKey()
{
	return SkullCrusherPlans::SaveKeySkullCrusherPlans;
}
