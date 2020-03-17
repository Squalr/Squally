#include "GladiatorSwordPlans.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string GladiatorSwordPlans::SaveKeyGladiatorSwordPlans = "gladiator-sword-plans";

GladiatorSwordPlans* GladiatorSwordPlans::create()
{
	GladiatorSwordPlans* instance = new GladiatorSwordPlans();

	instance->autorelease();

	return instance;
}

GladiatorSwordPlans::GladiatorSwordPlans() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}))
{
}

GladiatorSwordPlans::~GladiatorSwordPlans()
{
}

Item* GladiatorSwordPlans::craft()
{
	return GladiatorSword::create();
}

std::vector<std::tuple<Item*, int>> GladiatorSwordPlans::getReagentsInternal()
{
	return
	{
		{ Iron::create(), 8 },
		{ Coal::create(), 4 },
		{ Gold::create(), 2 },
	};
}

Item* GladiatorSwordPlans::clone()
{
	return GladiatorSwordPlans::create();
}

std::string GladiatorSwordPlans::getItemName()
{
	return GladiatorSwordPlans::SaveKeyGladiatorSwordPlans;
}

LocalizedString* GladiatorSwordPlans::getString()
{
	return Strings::Items_Equipment_Weapons_Swords_GladiatorSword::create();
}

std::string GladiatorSwordPlans::getIconResource()
{
	return ItemResources::Misc_SCROLL_1;
}

std::string GladiatorSwordPlans::getCraftedItemIconResource()
{
	return ItemResources::Equipment_Weapons_Swords_GladiatorSword;
}

std::string GladiatorSwordPlans::getSerializationKey()
{
	return GladiatorSwordPlans::SaveKeyGladiatorSwordPlans;
}
