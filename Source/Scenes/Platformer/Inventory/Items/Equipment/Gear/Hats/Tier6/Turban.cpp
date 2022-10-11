#include "Turban.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/Recipes/Gear/Hats/Tier6/TurbanPlans.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Turban::SaveKey = "turban";

Turban* Turban::create()
{
	Turban* instance = new Turban();

	instance->autorelease();

	return instance;
}

Turban::Turban() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}), ItemStats(
	// Health
	0,
	// Mana
	0,
	// Attack
	0,
	// Magic Attack
	0,
	// Armor
	0,
	// Speed
	0.05f
))
{
}

Turban::~Turban()
{
}

Item* Turban::clone()
{
	return Turban::create();
}

LocalizedString* Turban::getString()
{
	return Strings::Items_Equipment_Gear_Hats_Turban::create();
}

const std::string& Turban::getIconResource()
{
	return ItemResources::Equipment_Gear_Hats_Turban;
}

const std::string& Turban::getIdentifier()
{
	return Turban::SaveKey;
}

Vec2 Turban::getDisplayOffset()
{
	return Vec2(2.0f, 6.0f);
}

Recipe* Turban::getRecipe()
{
	return TurbanPlans::create();
}
