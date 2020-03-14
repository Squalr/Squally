#include "CrystalSwordPlans.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/ObjectResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string CrystalSwordPlans::SaveKeyCrystalSwordPlans = "crystal-sword-plans";

CrystalSwordPlans* CrystalSwordPlans::create()
{
	CrystalSwordPlans* instance = new CrystalSwordPlans();

	instance->autorelease();

	return instance;
}

CrystalSwordPlans::CrystalSwordPlans() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}))
{
}

CrystalSwordPlans::~CrystalSwordPlans()
{
}

Item* CrystalSwordPlans::craft()
{
	return CrystalSword::create();
}

std::vector<std::tuple<Item*, int>> CrystalSwordPlans::getReagentsInternal()
{
	return
	{
		{ Wood::create(), 2 },
		{ Iron::create(), 4 },
	};
}

Item* CrystalSwordPlans::clone()
{
	return CrystalSwordPlans::create();
}

std::string CrystalSwordPlans::getItemName()
{
	return CrystalSwordPlans::SaveKeyCrystalSwordPlans;
}

LocalizedString* CrystalSwordPlans::getString()
{
	return Strings::Items_Equipment_Weapons_Swords_CrystalSword::create();
}

std::string CrystalSwordPlans::getIconResource()
{
	return ObjectResources::Items_Crafting_SCROLL_1;
}

std::string CrystalSwordPlans::getCraftedItemIconResource()
{
	return ObjectResources::Items_Equipment_Weapons_Swords_CrystalSword;
}

std::string CrystalSwordPlans::getSerializationKey()
{
	return CrystalSwordPlans::SaveKeyCrystalSwordPlans;
}
