#include "DraksHelmPlans.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string DraksHelmPlans::SaveKey = "draks-helm-plans";

DraksHelmPlans* DraksHelmPlans::create()
{
	DraksHelmPlans* instance = new DraksHelmPlans();

	instance->autorelease();

	return instance;
}

DraksHelmPlans::DraksHelmPlans() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}))
{
}

DraksHelmPlans::~DraksHelmPlans()
{
}

std::vector<Item*> DraksHelmPlans::craft()
{
	return { DraksHelm::create() };
}

std::vector<std::tuple<Item*, int>> DraksHelmPlans::getReagentsInternal()
{
	return
	{
		{ Wood::create(), 2 },
		{ Iron::create(), 4 },
	};
}

Item* DraksHelmPlans::clone()
{
	return DraksHelmPlans::create();
}

LocalizedString* DraksHelmPlans::getString()
{
	return Strings::Items_Equipment_Gear_Hats_DraksHelm::create();
}

const std::string& DraksHelmPlans::getIconResource()
{
	return ItemResources::Misc_SCROLL_1;
}

std::string DraksHelmPlans::getCraftedItemIconResource()
{
	return ItemResources::Equipment_Gear_Hats_DraksHelm;
}

const std::string& DraksHelmPlans::getIdentifier()
{
	return DraksHelmPlans::SaveKey;
}
