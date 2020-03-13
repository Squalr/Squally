#include "SteelSwordPlans.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/ObjectResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string SteelSwordPlans::SaveKeySteelSwordPlans = "steel-sword-plans";

SteelSwordPlans* SteelSwordPlans::create()
{
	SteelSwordPlans* instance = new SteelSwordPlans();

	instance->autorelease();

	return instance;
}

SteelSwordPlans::SteelSwordPlans() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}))
{
}

SteelSwordPlans::~SteelSwordPlans()
{
}

Item* SteelSwordPlans::craft()
{
	return SteelSword::create();
}

std::map<Item*, int> SteelSwordPlans::getReagentsInternal()
{
	return
	{
		{ Wood::create(), 2 },
		{ Iron::create(), 4 },
	};
}

Item* SteelSwordPlans::clone()
{
	return SteelSwordPlans::create();
}

std::string SteelSwordPlans::getItemName()
{
	return SteelSwordPlans::SaveKeySteelSwordPlans;
}

LocalizedString* SteelSwordPlans::getString()
{
	return Strings::Items_Equipment_Weapons_Swords_SteelSword::create();
}

std::string SteelSwordPlans::getIconResource()
{
	return ObjectResources::Items_Crafting_SCROLL_1;
}

std::string SteelSwordPlans::getCraftedItemIconResource()
{
	return ObjectResources::Items_Equipment_Weapons_Swords_SteelSword;
}

std::string SteelSwordPlans::getSerializationKey()
{
	return SteelSwordPlans::SaveKeySteelSwordPlans;
}
