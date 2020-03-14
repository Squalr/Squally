#include "KatanaPlans.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/ObjectResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string KatanaPlans::SaveKeyKatanaPlans = "katana-plans";

KatanaPlans* KatanaPlans::create()
{
	KatanaPlans* instance = new KatanaPlans();

	instance->autorelease();

	return instance;
}

KatanaPlans::KatanaPlans() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}))
{
}

KatanaPlans::~KatanaPlans()
{
}

Item* KatanaPlans::craft()
{
	return Katana::create();
}

std::vector<std::tuple<Item*, int>> KatanaPlans::getReagentsInternal()
{
	return
	{
		{ LightWood::create(), 2 },
		{ Iron::create(), 3 },
		{ Coal::create(), 3 },
		{ Gold::create(), 4 },
	};
}

Item* KatanaPlans::clone()
{
	return KatanaPlans::create();
}

std::string KatanaPlans::getItemName()
{
	return KatanaPlans::SaveKeyKatanaPlans;
}

LocalizedString* KatanaPlans::getString()
{
	return Strings::Items_Equipment_Weapons_Swords_Katana::create();
}

std::string KatanaPlans::getIconResource()
{
	return ObjectResources::Items_Crafting_SCROLL_1;
}

std::string KatanaPlans::getCraftedItemIconResource()
{
	return ObjectResources::Items_Equipment_Weapons_Swords_Katana;
}

std::string KatanaPlans::getSerializationKey()
{
	return KatanaPlans::SaveKeyKatanaPlans;
}
