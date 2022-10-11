#include "TransmuteQuartzToEmerald.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string TransmuteQuartzToEmerald::SaveKey = "quartz-to-emerald-recipe";

TransmuteQuartzToEmerald* TransmuteQuartzToEmerald::create()
{
	TransmuteQuartzToEmerald* instance = new TransmuteQuartzToEmerald();

	instance->autorelease();

	return instance;
}

TransmuteQuartzToEmerald::TransmuteQuartzToEmerald() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}))
{
}

TransmuteQuartzToEmerald::~TransmuteQuartzToEmerald()
{
}

std::vector<Item*> TransmuteQuartzToEmerald::craft()
{
	return { Emerald::create() };
}

std::vector<std::tuple<Item*, int>> TransmuteQuartzToEmerald::getReagentsInternal()
{
	return
	{
		{ Quartz::create(), 4 },
		{ Coal::create(), 1 },
	};
}

Item* TransmuteQuartzToEmerald::clone()
{
	return TransmuteQuartzToEmerald::create();
}

LocalizedString* TransmuteQuartzToEmerald::getString()
{
	return Strings::Items_Crafting_Recipes_TransmuteQuartzToEmerald::create();
}

const std::string& TransmuteQuartzToEmerald::getIconResource()
{
	return ItemResources::Misc_SCROLL_1;
}

std::string TransmuteQuartzToEmerald::getCraftedItemIconResource()
{
	return ItemResources::Crafting_Smithing_Emerald;
}

const std::string& TransmuteQuartzToEmerald::getIdentifier()
{
	return TransmuteQuartzToEmerald::SaveKey;
}
