#include "FragGrenadeRecipe.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string FragGrenadeRecipe::SaveKey = "frag-grenade-recipe";

FragGrenadeRecipe* FragGrenadeRecipe::create()
{
	FragGrenadeRecipe* instance = new FragGrenadeRecipe();

	instance->autorelease();

	return instance;
}

FragGrenadeRecipe::FragGrenadeRecipe() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 66 }}))
{
}

FragGrenadeRecipe::~FragGrenadeRecipe()
{
}

std::vector<Item*> FragGrenadeRecipe::craft()
{
	return { FragGrenade::create() };
}

std::vector<std::tuple<Item*, int>> FragGrenadeRecipe::getReagentsInternal()
{
	return
	{
		{ Sulfur::create(), 2 },
		{ GunpowderT6::create(), 1 },
		{ PhoenixFeather::create(), 1 },
		{ Coal::create(), 2 },
	};
}

Item* FragGrenadeRecipe::clone()
{
	return FragGrenadeRecipe::create();
}

LocalizedString* FragGrenadeRecipe::getString()
{
	return Strings::Items_Consumables_Combat_FragGrenade::create();
}

const std::string& FragGrenadeRecipe::getIconResource()
{
	return ItemResources::Misc_SCROLL_1;
}

std::string FragGrenadeRecipe::getCraftedItemIconResource()
{
	return ItemResources::Consumables_Combat_T6_FragGrenade;
}

const std::string& FragGrenadeRecipe::getIdentifier()
{
	return FragGrenadeRecipe::SaveKey;
}
