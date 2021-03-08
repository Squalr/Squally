#include "CopperSwordPlans.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string CopperSwordPlans::SaveKey = "copper-sword-plans";

CopperSwordPlans* CopperSwordPlans::create()
{
	CopperSwordPlans* instance = new CopperSwordPlans();

	instance->autorelease();

	return instance;
}

CopperSwordPlans::CopperSwordPlans() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}))
{
}

CopperSwordPlans::~CopperSwordPlans()
{
}

std::vector<Item*> CopperSwordPlans::craft()
{
	return { CopperSword::create() };
}

std::vector<std::tuple<Item*, int>> CopperSwordPlans::getReagentsInternal()
{
	return
	{
		{ Wood::create(), 4 },
		{ Copper::create(), 4 },
	};
}

Item* CopperSwordPlans::clone()
{
	return CopperSwordPlans::create();
}

const std::string& CopperSwordPlans::getItemName()
{
	return CopperSwordPlans::SaveKey;
}

LocalizedString* CopperSwordPlans::getString()
{
	return Strings::Items_Equipment_Weapons_Swords_CopperSword::create();
}

const std::string& CopperSwordPlans::getIconResource()
{
	return ItemResources::Misc_SCROLL_1;
}

std::string CopperSwordPlans::getCraftedItemIconResource()
{
	return ItemResources::Equipment_Weapons_Swords_CopperSword;
}

const std::string& CopperSwordPlans::getSerializationKey()
{
	return CopperSwordPlans::SaveKey;
}
