#include "SuperiorHealthFlaskRecipe.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string SuperiorHealthFlaskRecipe::SaveKey = "superior-health-flask-recipe";

SuperiorHealthFlaskRecipe* SuperiorHealthFlaskRecipe::create()
{
	SuperiorHealthFlaskRecipe* instance = new SuperiorHealthFlaskRecipe();

	instance->autorelease();

	return instance;
}

SuperiorHealthFlaskRecipe::SuperiorHealthFlaskRecipe() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 25 }}))
{
}

SuperiorHealthFlaskRecipe::~SuperiorHealthFlaskRecipe()
{
}

std::vector<Item*> SuperiorHealthFlaskRecipe::craft()
{
	return { SuperiorHealthFlask::create() };
}

std::vector<std::tuple<Item*, int>> SuperiorHealthFlaskRecipe::getReagentsInternal()
{
	return
	{
		{ BlackMushroom::create(), 2 },
		{ Mandrake::create(), 2 },
	};
}

Item* SuperiorHealthFlaskRecipe::clone()
{
	return SuperiorHealthFlaskRecipe::create();
}

LocalizedString* SuperiorHealthFlaskRecipe::getString()
{
	return Strings::Items_Consumables_Health_SuperiorHealthFlask::create();
}

const std::string& SuperiorHealthFlaskRecipe::getIconResource()
{
	return ItemResources::Misc_SCROLL_1;
}

std::string SuperiorHealthFlaskRecipe::getCraftedItemIconResource()
{
	return ItemResources::Consumables_Potions_HealthFlaskSuperior;
}

const std::string& SuperiorHealthFlaskRecipe::getIdentifier()
{
	return SuperiorHealthFlaskRecipe::SaveKey;
}
