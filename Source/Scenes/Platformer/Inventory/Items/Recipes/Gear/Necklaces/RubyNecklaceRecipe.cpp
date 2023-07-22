#include "RubyNecklaceRecipe.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string RubyNecklaceRecipe::SaveKey = "ruby-necklace-recipe";

RubyNecklaceRecipe* RubyNecklaceRecipe::create()
{
	RubyNecklaceRecipe* instance = new RubyNecklaceRecipe();

	instance->autorelease();

	return instance;
}

RubyNecklaceRecipe::RubyNecklaceRecipe() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}))
{
}

RubyNecklaceRecipe::~RubyNecklaceRecipe()
{
}

std::vector<Item*> RubyNecklaceRecipe::craft()
{
	return { RubyNecklace::create() };
}

std::vector<std::tuple<Item*, int>> RubyNecklaceRecipe::getReagentsInternal()
{
	return
	{
		{ Iron::create(), 4 },
	};
}

Item* RubyNecklaceRecipe::clone()
{
	return RubyNecklaceRecipe::create();
}

LocalizedString* RubyNecklaceRecipe::getString()
{
	return Strings::Items_Equipment_Gear_Necklaces_RubyNecklace::create();
}

const std::string& RubyNecklaceRecipe::getIconResource()
{
	return ItemResources::Misc_SCROLL_1;
}

std::string RubyNecklaceRecipe::getCraftedItemIconResource()
{
	return ItemResources::Equipment_Gear_Necklaces_T5_RubyNecklace;
}

const std::string& RubyNecklaceRecipe::getIdentifier()
{
	return RubyNecklaceRecipe::SaveKey;
}
