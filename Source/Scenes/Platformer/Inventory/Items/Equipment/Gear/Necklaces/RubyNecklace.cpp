#include "RubyNecklace.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/Recipes/Gear/Necklaces/RubyNecklaceRecipe.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string RubyNecklace::SaveKey = "ruby-necklace";

RubyNecklace* RubyNecklace::create()
{
	RubyNecklace* instance = new RubyNecklace();

	instance->autorelease();

	return instance;
}

RubyNecklace::RubyNecklace() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 15 }}), ItemStats(
	// Health
	5,
	// Mana
	1,
	// Attack
	0,
	// Magic Attack
	0,
	// Armor
	0,
	// Speed
	0.025f
))
{
}

RubyNecklace::~RubyNecklace()
{
}

Item* RubyNecklace::clone()
{
	return RubyNecklace::create();
}

LocalizedString* RubyNecklace::getString()
{
	return Strings::Items_Equipment_Gear_Necklaces_RubyNecklace::create();
}

const std::string& RubyNecklace::getIconResource()
{
	return ItemResources::Equipment_Gear_Necklaces_T5_RubyNecklace;
}

const std::string& RubyNecklace::getIdentifier()
{
	return RubyNecklace::SaveKey;
}

Recipe* RubyNecklace::getRecipe()
{
	return RubyNecklaceRecipe::create();
}
