#include "EmeraldPendantRecipe.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string EmeraldPendantRecipe::SaveKey = "emerald-pendant-recipe";

EmeraldPendantRecipe* EmeraldPendantRecipe::create()
{
	EmeraldPendantRecipe* instance = new EmeraldPendantRecipe();

	instance->autorelease();

	return instance;
}

EmeraldPendantRecipe::EmeraldPendantRecipe() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}))
{
}

EmeraldPendantRecipe::~EmeraldPendantRecipe()
{
}

std::vector<Item*> EmeraldPendantRecipe::craft()
{
	return { EmeraldPendant::create() };
}

std::vector<std::tuple<Item*, int>> EmeraldPendantRecipe::getReagentsInternal()
{
	return
	{
		{ Iron::create(), 4 },
	};
}

Item* EmeraldPendantRecipe::clone()
{
	return EmeraldPendantRecipe::create();
}

LocalizedString* EmeraldPendantRecipe::getString()
{
	return Strings::Items_Equipment_Gear_Necklaces_EmeraldPendant::create();
}

const std::string& EmeraldPendantRecipe::getIconResource()
{
	return ItemResources::Misc_SCROLL_1;
}

std::string EmeraldPendantRecipe::getCraftedItemIconResource()
{
	return ItemResources::Equipment_Gear_Necklaces_EmeraldPendant;
}

const std::string& EmeraldPendantRecipe::getIdentifier()
{
	return EmeraldPendantRecipe::SaveKey;
}
