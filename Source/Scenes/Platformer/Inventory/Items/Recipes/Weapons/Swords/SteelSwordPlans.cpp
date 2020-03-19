#include "SteelSwordPlans.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string SteelSwordPlans::SaveKey = "steel-sword-plans";

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

std::vector<std::tuple<Item*, int>> SteelSwordPlans::getReagentsInternal()
{
	return
	{
		{ Iron::create(), 8 },
		{ Coal::create(), 4 },
	};
}

Item* SteelSwordPlans::clone()
{
	return SteelSwordPlans::create();
}

std::string SteelSwordPlans::getItemName()
{
	return SteelSwordPlans::SaveKey;
}

LocalizedString* SteelSwordPlans::getString()
{
	return Strings::Items_Equipment_Weapons_Swords_SteelSword::create();
}

std::string SteelSwordPlans::getIconResource()
{
	return ItemResources::Misc_SCROLL_1;
}

std::string SteelSwordPlans::getCraftedItemIconResource()
{
	return ItemResources::Equipment_Weapons_Swords_SteelSword;
}

std::string SteelSwordPlans::getSerializationKey()
{
	return SteelSwordPlans::SaveKey;
}
