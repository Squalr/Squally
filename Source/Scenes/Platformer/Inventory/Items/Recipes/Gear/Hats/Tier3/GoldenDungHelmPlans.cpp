#include "GoldenDungHelmPlans.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string GoldenDungHelmPlans::SaveKey = "golden-dung-helm-plans";

GoldenDungHelmPlans* GoldenDungHelmPlans::create()
{
	GoldenDungHelmPlans* instance = new GoldenDungHelmPlans();

	instance->autorelease();

	return instance;
}

GoldenDungHelmPlans::GoldenDungHelmPlans() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}))
{
}

GoldenDungHelmPlans::~GoldenDungHelmPlans()
{
}

std::vector<Item*> GoldenDungHelmPlans::craft()
{
	return { GoldenDungHelm::create() };
}

std::vector<std::tuple<Item*, int>> GoldenDungHelmPlans::getReagentsInternal()
{
	return
	{
		{ Gold::create(), 6 },
	};
}

Item* GoldenDungHelmPlans::clone()
{
	return GoldenDungHelmPlans::create();
}

LocalizedString* GoldenDungHelmPlans::getString()
{
	return Strings::Items_Equipment_Gear_Hats_GoldenDungHelm::create();
}

const std::string& GoldenDungHelmPlans::getIconResource()
{
	return ItemResources::Misc_SCROLL_1;
}

std::string GoldenDungHelmPlans::getCraftedItemIconResource()
{
	return ItemResources::Equipment_Gear_Hats_GoldenDungHelm;
}

const std::string& GoldenDungHelmPlans::getIdentifier()
{
	return GoldenDungHelmPlans::SaveKey;
}
