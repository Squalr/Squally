#include "WizardsHatArcanePlans.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string WizardsHatArcanePlans::SaveKey = "wizards-hat-arcane-plans";

WizardsHatArcanePlans* WizardsHatArcanePlans::create()
{
	WizardsHatArcanePlans* instance = new WizardsHatArcanePlans();

	instance->autorelease();

	return instance;
}

WizardsHatArcanePlans::WizardsHatArcanePlans() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}))
{
}

WizardsHatArcanePlans::~WizardsHatArcanePlans()
{
}

std::vector<Item*> WizardsHatArcanePlans::craft()
{
	return { WizardsHatArcane::create() };
}

std::vector<std::tuple<Item*, int>> WizardsHatArcanePlans::getReagentsInternal()
{
	return
	{
		{ Wood::create(), 2 },
		{ Iron::create(), 4 },
	};
}

Item* WizardsHatArcanePlans::clone()
{
	return WizardsHatArcanePlans::create();
}

LocalizedString* WizardsHatArcanePlans::getString()
{
	return Strings::Items_Equipment_Gear_Hats_WizardsHatArcane::create();
}

const std::string& WizardsHatArcanePlans::getIconResource()
{
	return ItemResources::Misc_SCROLL_1;
}

std::string WizardsHatArcanePlans::getCraftedItemIconResource()
{
	return ItemResources::Equipment_Gear_Hats_WizardsHatArcane;
}

const std::string& WizardsHatArcanePlans::getIdentifier()
{
	return WizardsHatArcanePlans::SaveKey;
}
