#include "TopazPendant.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/Recipes/Gear/Necklaces/TopazPendantRecipe.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string TopazPendant::SaveKey = "topaz-pendant";

TopazPendant* TopazPendant::create()
{
	TopazPendant* instance = new TopazPendant();

	instance->autorelease();

	return instance;
}

TopazPendant::TopazPendant() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 15 }}), ItemStats(
	// Health
	1,
	// Mana
	0,
	// Attack
	0,
	// Magic Attack
	0,
	// Armor
	0,
	// Speed
	0.005f
))
{
}

TopazPendant::~TopazPendant()
{
}

Item* TopazPendant::clone()
{
	return TopazPendant::create();
}

LocalizedString* TopazPendant::getString()
{
	return Strings::Items_Equipment_Gear_Necklaces_TopazPendant::create();
}

const std::string& TopazPendant::getIconResource()
{
	return ItemResources::Equipment_Gear_Necklaces_T1_TopazPendant;
}

const std::string& TopazPendant::getIdentifier()
{
	return TopazPendant::SaveKey;
}

Recipe* TopazPendant::getRecipe()
{
	return TopazPendantRecipe::create();
}
