#include "DismantleRecipe.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string DismantleRecipe::SaveKey = "Dismantle-recipe";

DismantleRecipe* DismantleRecipe::create()
{
	DismantleRecipe* instance = new DismantleRecipe();

	instance->autorelease();

	return instance;
}

DismantleRecipe::DismantleRecipe() : super()
{
}

DismantleRecipe::~DismantleRecipe()
{
}

std::vector<Item*> DismantleRecipe::craft()
{
	return { BoneAxe::create() };
}

std::vector<std::tuple<Item*, int>> DismantleRecipe::getReagentsInternal()
{
	return
	{
		{ Wood::create(), 2 },
		{ Iron::create(), 4 },
	};
}

Item* DismantleRecipe::clone()
{
	return DismantleRecipe::create();
}

std::string DismantleRecipe::getItemName()
{
	return DismantleRecipe::SaveKey;
}

LocalizedString* DismantleRecipe::getString()
{
	return Strings::Items_Equipment_Weapons_Axes_BoneAxe::create();
}

std::string DismantleRecipe::getIconResource()
{
	return ItemResources::Misc_SCROLL_1;
}

std::string DismantleRecipe::getCraftedItemIconResource()
{
	return ItemResources::Equipment_Weapons_Axes_BoneAxe;
}

std::string DismantleRecipe::getSerializationKey()
{
	return DismantleRecipe::SaveKey;
}
