#include "FireSwordPlans.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string FireSwordPlans::SaveKey = "fire-sword-plans";

FireSwordPlans* FireSwordPlans::create()
{
	FireSwordPlans* instance = new FireSwordPlans();

	instance->autorelease();

	return instance;
}

FireSwordPlans::FireSwordPlans() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}))
{
}

FireSwordPlans::~FireSwordPlans()
{
}

std::vector<Item*> FireSwordPlans::craft()
{
	return { FireSword::create() };
}

std::vector<std::tuple<Item*, int>> FireSwordPlans::getReagentsInternal()
{
	return
	{
		{ Wood::create(), 4 },
		{ Iron::create(), 4 },
		{ Coal::create(), 4 },
	};
}

Item* FireSwordPlans::clone()
{
	return FireSwordPlans::create();
}

const std::string& FireSwordPlans::getItemName()
{
	return FireSwordPlans::SaveKey;
}

LocalizedString* FireSwordPlans::getString()
{
	return Strings::Items_Equipment_Weapons_Swords_FireSword::create();
}

const std::string& FireSwordPlans::getIconResource()
{
	return ItemResources::Misc_SCROLL_1;
}

std::string FireSwordPlans::getCraftedItemIconResource()
{
	return ItemResources::Equipment_Weapons_Special_FireSword;
}

const std::string& FireSwordPlans::getSerializationKey()
{
	return FireSwordPlans::SaveKey;
}
