#include "TheGoldenEaglePlans.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string TheGoldenEaglePlans::SaveKey = "the-golden-eagle-plans";

TheGoldenEaglePlans* TheGoldenEaglePlans::create()
{
	TheGoldenEaglePlans* instance = new TheGoldenEaglePlans();

	instance->autorelease();

	return instance;
}

TheGoldenEaglePlans::TheGoldenEaglePlans() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}))
{
}

TheGoldenEaglePlans::~TheGoldenEaglePlans()
{
}

std::vector<Item*> TheGoldenEaglePlans::craft()
{
	return { TheGoldenEagle::create() };
}

std::vector<std::tuple<Item*, int>> TheGoldenEaglePlans::getReagentsInternal()
{
	return
	{
		{ Gold::create(), 10 },
	};
}

Item* TheGoldenEaglePlans::clone()
{
	return TheGoldenEaglePlans::create();
}

LocalizedString* TheGoldenEaglePlans::getString()
{
	return Strings::Items_Equipment_Gear_Hats_TheGoldenEagle::create();
}

const std::string& TheGoldenEaglePlans::getIconResource()
{
	return ItemResources::Misc_SCROLL_1;
}

std::string TheGoldenEaglePlans::getCraftedItemIconResource()
{
	return ItemResources::Equipment_Gear_Hats_TheGoldenEagle;
}

const std::string& TheGoldenEaglePlans::getIdentifier()
{
	return TheGoldenEaglePlans::SaveKey;
}
