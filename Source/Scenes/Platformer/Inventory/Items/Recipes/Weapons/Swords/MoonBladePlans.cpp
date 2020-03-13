#include "MoonBladePlans.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/ObjectResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string MoonBladePlans::SaveKeyMoonBladePlans = "moon-blade-plans";

MoonBladePlans* MoonBladePlans::create()
{
	MoonBladePlans* instance = new MoonBladePlans();

	instance->autorelease();

	return instance;
}

MoonBladePlans::MoonBladePlans() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}))
{
}

MoonBladePlans::~MoonBladePlans()
{
}

Item* MoonBladePlans::craft()
{
	return MoonBlade::create();
}

std::map<Item*, int> MoonBladePlans::getReagentsInternal()
{
	return
	{
		{ Wood::create(), 2 },
		{ Iron::create(), 4 },
	};
}

Item* MoonBladePlans::clone()
{
	return MoonBladePlans::create();
}

std::string MoonBladePlans::getItemName()
{
	return MoonBladePlans::SaveKeyMoonBladePlans;
}

LocalizedString* MoonBladePlans::getString()
{
	return Strings::Items_Equipment_Weapons_Swords_MoonBlade::create();
}

std::string MoonBladePlans::getIconResource()
{
	return ObjectResources::Items_Crafting_SCROLL_1;
}

std::string MoonBladePlans::getCraftedItemIconResource()
{
	return ObjectResources::Items_Equipment_Weapons_Swords_MoonBlade;
}

std::string MoonBladePlans::getSerializationKey()
{
	return MoonBladePlans::SaveKeyMoonBladePlans;
}
