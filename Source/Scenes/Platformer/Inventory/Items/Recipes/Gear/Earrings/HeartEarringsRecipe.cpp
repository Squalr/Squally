#include "HeartEarringsRecipe.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string HeartEarringsRecipe::SaveKey = "heart-earrings-recipe";

HeartEarringsRecipe* HeartEarringsRecipe::create()
{
	HeartEarringsRecipe* instance = new HeartEarringsRecipe();

	instance->autorelease();

	return instance;
}

HeartEarringsRecipe::HeartEarringsRecipe() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}))
{
}

HeartEarringsRecipe::~HeartEarringsRecipe()
{
}

std::vector<Item*> HeartEarringsRecipe::craft()
{
	return { HeartEarrings::create() };
}

std::vector<std::tuple<Item*, int>> HeartEarringsRecipe::getReagentsInternal()
{
	return
	{
		{ Gold::create(), 2 },
		{ Ruby::create(), 1 },
	};
}

Item* HeartEarringsRecipe::clone()
{
	return HeartEarringsRecipe::create();
}

LocalizedString* HeartEarringsRecipe::getString()
{
	return Strings::Items_Equipment_Gear_Earrings_HeartEarrings::create();
}

const std::string& HeartEarringsRecipe::getIconResource()
{
	return ItemResources::Misc_SCROLL_1;
}

std::string HeartEarringsRecipe::getCraftedItemIconResource()
{
	return ItemResources::Equipment_Gear_Earrings_HeartEarrings;
}

const std::string& HeartEarringsRecipe::getIdentifier()
{
	return HeartEarringsRecipe::SaveKey;
}
