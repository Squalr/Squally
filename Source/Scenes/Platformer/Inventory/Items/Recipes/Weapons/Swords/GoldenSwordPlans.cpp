#include "GoldenSwordPlans.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string GoldenSwordPlans::SaveKey = "golden-sword-plans";

GoldenSwordPlans* GoldenSwordPlans::create()
{
	GoldenSwordPlans* instance = new GoldenSwordPlans();

	instance->autorelease();

	return instance;
}

GoldenSwordPlans::GoldenSwordPlans() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}))
{
}

GoldenSwordPlans::~GoldenSwordPlans()
{
}

std::vector<Item*> GoldenSwordPlans::craft()
{
	return { GoldenSword::create() };
}

std::vector<std::tuple<Item*, int>> GoldenSwordPlans::getReagentsInternal()
{
	return
	{
		{ Iron::create(), 8 },
		{ Coal::create(), 4 },
		{ Gold::create(), 2 },
	};
}

Item* GoldenSwordPlans::clone()
{
	return GoldenSwordPlans::create();
}

const std::string& GoldenSwordPlans::getItemName()
{
	return GoldenSwordPlans::SaveKey;
}

LocalizedString* GoldenSwordPlans::getString()
{
	return Strings::Items_Equipment_Weapons_Swords_GoldenSword::create();
}

const std::string& GoldenSwordPlans::getIconResource()
{
	return ItemResources::Misc_SCROLL_1;
}

std::string GoldenSwordPlans::getCraftedItemIconResource()
{
	return ItemResources::Equipment_Weapons_Swords_GoldenSword;
}

const std::string& GoldenSwordPlans::getSerializationKey()
{
	return GoldenSwordPlans::SaveKey;
}
