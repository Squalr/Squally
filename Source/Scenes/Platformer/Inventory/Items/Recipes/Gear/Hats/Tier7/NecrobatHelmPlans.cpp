#include "NecrobatHelmPlans.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string NecrobatHelmPlans::SaveKey = "necrobat-helm-plans";

NecrobatHelmPlans* NecrobatHelmPlans::create()
{
	NecrobatHelmPlans* instance = new NecrobatHelmPlans();

	instance->autorelease();

	return instance;
}

NecrobatHelmPlans::NecrobatHelmPlans() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}))
{
}

NecrobatHelmPlans::~NecrobatHelmPlans()
{
}

std::vector<Item*> NecrobatHelmPlans::craft()
{
	return { NecrobatHelm::create() };
}

std::vector<std::tuple<Item*, int>> NecrobatHelmPlans::getReagentsInternal()
{
	return
	{
		{ Wood::create(), 2 },
		{ Iron::create(), 4 },
	};
}

Item* NecrobatHelmPlans::clone()
{
	return NecrobatHelmPlans::create();
}

LocalizedString* NecrobatHelmPlans::getString()
{
	return Strings::Items_Equipment_Gear_Hats_NecrobatHelm::create();
}

const std::string& NecrobatHelmPlans::getIconResource()
{
	return ItemResources::Misc_SCROLL_1;
}

std::string NecrobatHelmPlans::getCraftedItemIconResource()
{
	return ItemResources::Equipment_Gear_Hats_NecrobatHelm;
}

const std::string& NecrobatHelmPlans::getIdentifier()
{
	return NecrobatHelmPlans::SaveKey;
}
