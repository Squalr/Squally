#include "TopazPendantRecipe.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string TopazPendantRecipe::SaveKey = "topaz-pendant-recipe";

TopazPendantRecipe* TopazPendantRecipe::create()
{
	TopazPendantRecipe* instance = new TopazPendantRecipe();

	instance->autorelease();

	return instance;
}

TopazPendantRecipe::TopazPendantRecipe() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}))
{
}

TopazPendantRecipe::~TopazPendantRecipe()
{
}

std::vector<Item*> TopazPendantRecipe::craft()
{
	return { TopazPendant::create() };
}

std::vector<std::tuple<Item*, int>> TopazPendantRecipe::getReagentsInternal()
{
	return
	{
		{ Iron::create(), 4 },
	};
}

Item* TopazPendantRecipe::clone()
{
	return TopazPendantRecipe::create();
}

LocalizedString* TopazPendantRecipe::getString()
{
	return Strings::Items_Equipment_Gear_Necklaces_TopazPendant::create();
}

const std::string& TopazPendantRecipe::getIconResource()
{
	return ItemResources::Misc_SCROLL_1;
}

std::string TopazPendantRecipe::getCraftedItemIconResource()
{
	return ItemResources::Equipment_Gear_Necklaces_TopazPendant;
}

const std::string& TopazPendantRecipe::getIdentifier()
{
	return TopazPendantRecipe::SaveKey;
}
