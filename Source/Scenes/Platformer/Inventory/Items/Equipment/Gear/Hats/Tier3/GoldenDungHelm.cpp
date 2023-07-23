#include "GoldenDungHelm.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/Recipes/Gear/Hats/Tier3/GoldenDungHelmPlans.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string GoldenDungHelm::SaveKey = "golden-dung-helm";

GoldenDungHelm* GoldenDungHelm::create()
{
	GoldenDungHelm* instance = new GoldenDungHelm();

	instance->autorelease();

	return instance;
}

GoldenDungHelm::GoldenDungHelm() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}), ItemStats(
	// Health
	WARRIOR_HP(3),
	// Mana
	WARRIOR_MP(3),
	// Attack
	WARRIOR_ATTACK(3),
	// Magic Attack
	WARRIOR_MAGIC_ATTACK(3),
	// Armor
	WARRIOR_ARMOR(3),
	// Speed
	WARRIOR_SPEED(3)
))
{
}

GoldenDungHelm::~GoldenDungHelm()
{
}

Item* GoldenDungHelm::clone()
{
	return GoldenDungHelm::create();
}

LocalizedString* GoldenDungHelm::getString()
{
	return Strings::Items_Equipment_Gear_Hats_GoldenDungHelm::create();
}

const std::string& GoldenDungHelm::getIconResource()
{
	return ItemResources::Equipment_Gear_Hats_Tier3_GoldenDungHelm;
}

const std::string& GoldenDungHelm::getIdentifier()
{
	return GoldenDungHelm::SaveKey;
}

Vec2 GoldenDungHelm::getDisplayOffset()
{
	return Vec2(8.0f, 26.0f);
}

Recipe* GoldenDungHelm::getRecipe()
{
	return GoldenDungHelmPlans::create();
}
