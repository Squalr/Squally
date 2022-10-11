#include "GlowingPendantRecipe.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string GlowingPendantRecipe::SaveKey = "glowing-pendant-recipe";

GlowingPendantRecipe* GlowingPendantRecipe::create()
{
	GlowingPendantRecipe* instance = new GlowingPendantRecipe();

	instance->autorelease();

	return instance;
}

GlowingPendantRecipe::GlowingPendantRecipe() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}))
{
}

GlowingPendantRecipe::~GlowingPendantRecipe()
{
}

std::vector<Item*> GlowingPendantRecipe::craft()
{
	return { GlowingPendant::create() };
}

std::vector<std::tuple<Item*, int>> GlowingPendantRecipe::getReagentsInternal()
{
	return
	{
		{ Iron::create(), 4 },
	};
}

Item* GlowingPendantRecipe::clone()
{
	return GlowingPendantRecipe::create();
}

LocalizedString* GlowingPendantRecipe::getString()
{
	return Strings::Items_Equipment_Gear_Necklaces_GlowingPendant::create();
}

const std::string& GlowingPendantRecipe::getIconResource()
{
	return ItemResources::Misc_SCROLL_1;
}

std::string GlowingPendantRecipe::getCraftedItemIconResource()
{
	return ItemResources::Equipment_Gear_Necklaces_GlowingPendant;
}

const std::string& GlowingPendantRecipe::getIdentifier()
{
	return GlowingPendantRecipe::SaveKey;
}
