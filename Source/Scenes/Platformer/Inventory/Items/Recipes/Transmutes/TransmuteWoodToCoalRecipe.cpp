#include "TransmuteWoodToCoalRecipe.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string TransmuteWoodToCoalRecipe::SaveKey = "wood-to-coal-recipe";

TransmuteWoodToCoalRecipe* TransmuteWoodToCoalRecipe::create()
{
	TransmuteWoodToCoalRecipe* instance = new TransmuteWoodToCoalRecipe();

	instance->autorelease();

	return instance;
}

TransmuteWoodToCoalRecipe::TransmuteWoodToCoalRecipe() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}))
{
}

TransmuteWoodToCoalRecipe::~TransmuteWoodToCoalRecipe()
{
}

Item* TransmuteWoodToCoalRecipe::craft()
{
	return Coal::create();
}

std::vector<std::tuple<Item*, int>> TransmuteWoodToCoalRecipe::getReagentsInternal()
{
	return
	{
		{ Wood::create(), 2 },
	};
}

Item* TransmuteWoodToCoalRecipe::clone()
{
	return TransmuteWoodToCoalRecipe::create();
}

std::string TransmuteWoodToCoalRecipe::getItemName()
{
	return TransmuteWoodToCoalRecipe::SaveKey;
}

LocalizedString* TransmuteWoodToCoalRecipe::getString()
{
	return Strings::Items_Crafting_Recipes_TransmuteWoodToCoal::create();
}

std::string TransmuteWoodToCoalRecipe::getIconResource()
{
	return ItemResources::Misc_SCROLL_1;
}

std::string TransmuteWoodToCoalRecipe::getCraftedItemIconResource()
{
	return ItemResources::Crafting_Smithing_Coal;
}

std::string TransmuteWoodToCoalRecipe::getSerializationKey()
{
	return TransmuteWoodToCoalRecipe::SaveKey;
}
