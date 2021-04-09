#include "JoustingHelmetPlans.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string JoustingHelmetPlans::SaveKey = "jousting-helmet-plans";

JoustingHelmetPlans* JoustingHelmetPlans::create()
{
	JoustingHelmetPlans* instance = new JoustingHelmetPlans();

	instance->autorelease();

	return instance;
}

JoustingHelmetPlans::JoustingHelmetPlans() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}))
{
}

JoustingHelmetPlans::~JoustingHelmetPlans()
{
}

std::vector<Item*> JoustingHelmetPlans::craft()
{
	return { JoustingHelmet::create() };
}

std::vector<std::tuple<Item*, int>> JoustingHelmetPlans::getReagentsInternal()
{
	return
	{
		{ Wood::create(), 2 },
		{ Iron::create(), 4 },
	};
}

Item* JoustingHelmetPlans::clone()
{
	return JoustingHelmetPlans::create();
}

LocalizedString* JoustingHelmetPlans::getString()
{
	return Strings::Items_Equipment_Gear_Hats_JoustingHelmet::create();
}

const std::string& JoustingHelmetPlans::getIconResource()
{
	return ItemResources::Misc_SCROLL_1;
}

std::string JoustingHelmetPlans::getCraftedItemIconResource()
{
	return ItemResources::Equipment_Gear_Hats_JoustingHelmet;
}

const std::string& JoustingHelmetPlans::getIdentifier()
{
	return JoustingHelmetPlans::SaveKey;
}
