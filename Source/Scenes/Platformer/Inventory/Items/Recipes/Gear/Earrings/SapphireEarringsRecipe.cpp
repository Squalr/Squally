#include "SapphireEarringsRecipe.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string SapphireEarringsRecipe::SaveKey = "sapphire-earrings-recipe";

SapphireEarringsRecipe* SapphireEarringsRecipe::create()
{
	SapphireEarringsRecipe* instance = new SapphireEarringsRecipe();

	instance->autorelease();

	return instance;
}

SapphireEarringsRecipe::SapphireEarringsRecipe() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}))
{
}

SapphireEarringsRecipe::~SapphireEarringsRecipe()
{
}

std::vector<Item*> SapphireEarringsRecipe::craft()
{
	return { SapphireEarrings::create() };
}

std::vector<std::tuple<Item*, int>> SapphireEarringsRecipe::getReagentsInternal()
{
	return
	{
		{ Gold::create(), 2 },
		{ Sapphire::create(), 1 },
	};
}

Item* SapphireEarringsRecipe::clone()
{
	return SapphireEarringsRecipe::create();
}

LocalizedString* SapphireEarringsRecipe::getString()
{
	return Strings::Items_Equipment_Gear_Earrings_SapphireEarrings::create();
}

const std::string& SapphireEarringsRecipe::getIconResource()
{
	return ItemResources::Misc_SCROLL_1;
}

std::string SapphireEarringsRecipe::getCraftedItemIconResource()
{
	return ItemResources::Equipment_Gear_Earrings_SapphireEarrings;
}

const std::string& SapphireEarringsRecipe::getIdentifier()
{
	return SapphireEarringsRecipe::SaveKey;
}
