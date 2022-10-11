#include "CrystalEarringsRecipe.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string CrystalEarringsRecipe::SaveKey = "crystal-earrings-recipe";

CrystalEarringsRecipe* CrystalEarringsRecipe::create()
{
	CrystalEarringsRecipe* instance = new CrystalEarringsRecipe();

	instance->autorelease();

	return instance;
}

CrystalEarringsRecipe::CrystalEarringsRecipe() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}))
{
}

CrystalEarringsRecipe::~CrystalEarringsRecipe()
{
}

std::vector<Item*> CrystalEarringsRecipe::craft()
{
	return { CrystalEarrings::create() };
}

std::vector<std::tuple<Item*, int>> CrystalEarringsRecipe::getReagentsInternal()
{
	return
	{
		{ Iron::create(), 4 },
	};
}

Item* CrystalEarringsRecipe::clone()
{
	return CrystalEarringsRecipe::create();
}

LocalizedString* CrystalEarringsRecipe::getString()
{
	return Strings::Items_Equipment_Gear_Earrings_CrystalEarrings::create();
}

const std::string& CrystalEarringsRecipe::getIconResource()
{
	return ItemResources::Misc_SCROLL_1;
}

std::string CrystalEarringsRecipe::getCraftedItemIconResource()
{
	return ItemResources::Equipment_Gear_Earrings_CrystalEarrings;
}

const std::string& CrystalEarringsRecipe::getIdentifier()
{
	return CrystalEarringsRecipe::SaveKey;
}
