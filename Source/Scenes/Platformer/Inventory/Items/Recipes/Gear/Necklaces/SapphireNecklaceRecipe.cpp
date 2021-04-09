#include "SapphireNecklaceRecipe.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string SapphireNecklaceRecipe::SaveKey = "sapphire-necklace-recipe";

SapphireNecklaceRecipe* SapphireNecklaceRecipe::create()
{
	SapphireNecklaceRecipe* instance = new SapphireNecklaceRecipe();

	instance->autorelease();

	return instance;
}

SapphireNecklaceRecipe::SapphireNecklaceRecipe() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}))
{
}

SapphireNecklaceRecipe::~SapphireNecklaceRecipe()
{
}

std::vector<Item*> SapphireNecklaceRecipe::craft()
{
	return { SapphireNecklace::create() };
}

std::vector<std::tuple<Item*, int>> SapphireNecklaceRecipe::getReagentsInternal()
{
	return
	{
		{ Iron::create(), 4 },
	};
}

Item* SapphireNecklaceRecipe::clone()
{
	return SapphireNecklaceRecipe::create();
}

LocalizedString* SapphireNecklaceRecipe::getString()
{
	return Strings::Items_Equipment_Gear_Necklaces_SapphireNecklace::create();
}

const std::string& SapphireNecklaceRecipe::getIconResource()
{
	return ItemResources::Misc_SCROLL_1;
}

std::string SapphireNecklaceRecipe::getCraftedItemIconResource()
{
	return ItemResources::Equipment_Gear_Necklaces_SapphireNecklace;
}

const std::string& SapphireNecklaceRecipe::getIdentifier()
{
	return SapphireNecklaceRecipe::SaveKey;
}
