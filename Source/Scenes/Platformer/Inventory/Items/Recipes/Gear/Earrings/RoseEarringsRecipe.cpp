#include "RoseEarringsRecipe.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string RoseEarringsRecipe::SaveKey = "rose-earrings-recipe";

RoseEarringsRecipe* RoseEarringsRecipe::create()
{
	RoseEarringsRecipe* instance = new RoseEarringsRecipe();

	instance->autorelease();

	return instance;
}

RoseEarringsRecipe::RoseEarringsRecipe() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}))
{
}

RoseEarringsRecipe::~RoseEarringsRecipe()
{
}

std::vector<Item*> RoseEarringsRecipe::craft()
{
	return { RoseEarrings::create() };
}

std::vector<std::tuple<Item*, int>> RoseEarringsRecipe::getReagentsInternal()
{
	return
	{
		{ Gold::create(), 2 },
		{ Ruby::create(), 1 },
	};
}

Item* RoseEarringsRecipe::clone()
{
	return RoseEarringsRecipe::create();
}

LocalizedString* RoseEarringsRecipe::getString()
{
	return Strings::Items_Equipment_Gear_Earrings_RoseEarrings::create();
}

const std::string& RoseEarringsRecipe::getIconResource()
{
	return ItemResources::Misc_SCROLL_1;
}

std::string RoseEarringsRecipe::getCraftedItemIconResource()
{
	return ItemResources::Equipment_Gear_Earrings_RoseEarrings;
}

const std::string& RoseEarringsRecipe::getIdentifier()
{
	return RoseEarringsRecipe::SaveKey;
}
