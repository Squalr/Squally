#include "JoustingHelmet.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/Recipes/Gear/Hats/Tier4/JoustingHelmetPlans.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string JoustingHelmet::SaveKey = "jousting-helmet";

JoustingHelmet* JoustingHelmet::create()
{
	JoustingHelmet* instance = new JoustingHelmet();

	instance->autorelease();

	return instance;
}

JoustingHelmet::JoustingHelmet() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}), ItemStats(
	// Health
	WARRIOR_HP(4),
	// Mana
	WARRIOR_MP(4),
	// Attack
	WARRIOR_ATTACK(4),
	// Magic Attack
	WARRIOR_MAGIC_ATTACK(4),
	// Armor
	WARRIOR_ARMOR(4),
	// Speed
	WARRIOR_SPEED(4)
))
{
}

JoustingHelmet::~JoustingHelmet()
{
}

Item* JoustingHelmet::clone()
{
	return JoustingHelmet::create();
}

LocalizedString* JoustingHelmet::getString()
{
	return Strings::Items_Equipment_Gear_Hats_JoustingHelmet::create();
}

const std::string& JoustingHelmet::getIconResource()
{
	return ItemResources::Equipment_Gear_Hats_Tier4_JoustingHelmet;
}

const std::string& JoustingHelmet::getIdentifier()
{
	return JoustingHelmet::SaveKey;
}

Vec2 JoustingHelmet::getDisplayOffset()
{
	return Vec2(-40.0f, 34.0f);
}

Recipe* JoustingHelmet::getRecipe()
{
	return JoustingHelmetPlans::create();
}
