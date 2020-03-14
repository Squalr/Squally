#include "IronSwordPlans.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/ObjectResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string IronSwordPlans::SaveKeyIronSwordPlans = "iron-sword-plans";

IronSwordPlans* IronSwordPlans::create()
{
	IronSwordPlans* instance = new IronSwordPlans();

	instance->autorelease();

	return instance;
}

IronSwordPlans::IronSwordPlans() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}))
{
}

IronSwordPlans::~IronSwordPlans()
{
}

Item* IronSwordPlans::craft()
{
	return IronSword::create();
}

std::vector<std::tuple<Item*, int>> IronSwordPlans::getReagentsInternal()
{
	return
	{
		{ Wood::create(), 2 },
		{ Iron::create(), 4 },
	};
}

Item* IronSwordPlans::clone()
{
	return IronSwordPlans::create();
}

std::string IronSwordPlans::getItemName()
{
	return IronSwordPlans::SaveKeyIronSwordPlans;
}

LocalizedString* IronSwordPlans::getString()
{
	return Strings::Items_Equipment_Weapons_Swords_IronSword::create();
}

std::string IronSwordPlans::getIconResource()
{
	return ObjectResources::Items_Crafting_SCROLL_1;
}

std::string IronSwordPlans::getCraftedItemIconResource()
{
	return ObjectResources::Items_Equipment_Weapons_Swords_IronSword;
}

std::string IronSwordPlans::getSerializationKey()
{
	return IronSwordPlans::SaveKeyIronSwordPlans;
}
