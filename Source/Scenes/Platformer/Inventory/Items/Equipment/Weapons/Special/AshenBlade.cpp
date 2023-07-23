#include "AshenBlade.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/Recipes/Weapons/Special/AshenBladePlans.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string AshenBlade::SaveKey = "ashen-blade";

AshenBlade* AshenBlade::create()
{
	AshenBlade* instance = new AshenBlade();

	instance->autorelease();

	return instance;
}

AshenBlade::AshenBlade() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}), SWORD_DAMAGE_MIN(10), SWORD_DAMAGE_MAX(10), ItemStats(
	// Health
	10,
	// Mana
	10,
	// Attack
	0,
	// Magic Attack
	0,
	// Armor
	0,
	// Speed
	0.25f
))
{
}

AshenBlade::~AshenBlade()
{
}

Item* AshenBlade::clone()
{
	return AshenBlade::create();
}

LocalizedString* AshenBlade::getString()
{
	return Strings::Items_Equipment_Weapons_Swords_AshenBlade::create();
}

const std::string& AshenBlade::getIconResource()
{
	return ItemResources::Equipment_Weapons_Special_AshenBlade;
}

const std::string& AshenBlade::getIdentifier()
{
	return AshenBlade::SaveKey;
}

Vec2 AshenBlade::getDisplayOffset()
{
	return Vec2(0.0f, -12.0f);
}

Recipe* AshenBlade::getRecipe()
{
	return AshenBladePlans::create();
}
