#include "WitchesHatPlans.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string WitchesHatPlans::SaveKey = "witches-hat-plans";

WitchesHatPlans* WitchesHatPlans::create()
{
	WitchesHatPlans* instance = new WitchesHatPlans();

	instance->autorelease();

	return instance;
}

WitchesHatPlans::WitchesHatPlans() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}))
{
}

WitchesHatPlans::~WitchesHatPlans()
{
}

std::vector<Item*> WitchesHatPlans::craft()
{
	return { WitchesHat::create() };
}

std::vector<std::tuple<Item*, int>> WitchesHatPlans::getReagentsInternal()
{
	return
	{
		{ Wood::create(), 2 },
		{ Iron::create(), 4 },
	};
}

Item* WitchesHatPlans::clone()
{
	return WitchesHatPlans::create();
}

LocalizedString* WitchesHatPlans::getString()
{
	return Strings::Items_Equipment_Gear_Hats_WitchesHat::create();
}

const std::string& WitchesHatPlans::getIconResource()
{
	return ItemResources::Misc_SCROLL_1;
}

std::string WitchesHatPlans::getCraftedItemIconResource()
{
	return ItemResources::Equipment_Gear_Hats_WitchesHat;
}

const std::string& WitchesHatPlans::getIdentifier()
{
	return WitchesHatPlans::SaveKey;
}
