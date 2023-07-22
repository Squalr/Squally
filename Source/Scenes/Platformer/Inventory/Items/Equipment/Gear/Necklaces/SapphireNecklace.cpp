#include "SapphireNecklace.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/Recipes/Gear/Necklaces/SapphireNecklaceRecipe.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string SapphireNecklace::SaveKey = "sapphire-necklace";

SapphireNecklace* SapphireNecklace::create()
{
	SapphireNecklace* instance = new SapphireNecklace();

	instance->autorelease();

	return instance;
}

SapphireNecklace::SapphireNecklace() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 15 }}), ItemStats(
	// Health
	4,
	// Mana
	0,
	// Attack
	0,
	// Magic Attack
	0,
	// Armor
	0,
	// Speed
	0.02f
))
{
}

SapphireNecklace::~SapphireNecklace()
{
}

Item* SapphireNecklace::clone()
{
	return SapphireNecklace::create();
}

LocalizedString* SapphireNecklace::getString()
{
	return Strings::Items_Equipment_Gear_Necklaces_SapphireNecklace::create();
}

const std::string& SapphireNecklace::getIconResource()
{
	return ItemResources::Equipment_Gear_Necklaces_T4_SapphireNecklace;
}

const std::string& SapphireNecklace::getIdentifier()
{
	return SapphireNecklace::SaveKey;
}

Recipe* SapphireNecklace::getRecipe()
{
	return SapphireNecklaceRecipe::create();
}
