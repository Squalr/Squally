#include "MithrilHelmPlans.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string MithrilHelmPlans::SaveKey = "mithril-helm-plans";

MithrilHelmPlans* MithrilHelmPlans::create()
{
	MithrilHelmPlans* instance = new MithrilHelmPlans();

	instance->autorelease();

	return instance;
}

MithrilHelmPlans::MithrilHelmPlans() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}))
{
}

MithrilHelmPlans::~MithrilHelmPlans()
{
}

std::vector<Item*> MithrilHelmPlans::craft()
{
	return { MithrilHelm::create() };
}

std::vector<std::tuple<Item*, int>> MithrilHelmPlans::getReagentsInternal()
{
	return
	{
		{ Diamond::create(), 1 },
		{ Mithril::create(), 2 },
		{ Coal::create(), 2 },
	};
}

Item* MithrilHelmPlans::clone()
{
	return MithrilHelmPlans::create();
}

LocalizedString* MithrilHelmPlans::getString()
{
	return Strings::Items_Equipment_Gear_Hats_MithrilHelm::create();
}

const std::string& MithrilHelmPlans::getIconResource()
{
	return ItemResources::Misc_SCROLL_1;
}

std::string MithrilHelmPlans::getCraftedItemIconResource()
{
	return ItemResources::Equipment_Gear_Hats_Tier5_MithrilHelm;
}

const std::string& MithrilHelmPlans::getIdentifier()
{
	return MithrilHelmPlans::SaveKey;
}
