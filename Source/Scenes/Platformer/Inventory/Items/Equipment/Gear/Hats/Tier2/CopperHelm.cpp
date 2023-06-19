#include "CopperHelm.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/Recipes/Gear/Hats/Tier2/CopperHelmPlans.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string CopperHelm::SaveKey = "copper-helm";

CopperHelm* CopperHelm::create()
{
	CopperHelm* instance = new CopperHelm();

	instance->autorelease();

	return instance;
}

CopperHelm::CopperHelm() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 15 }}), ItemStats(
	// Health
	WARRIOR_HP(2),
	// Mana
	WARRIOR_MP(2),
	// Attack
	WARRIOR_ATTACK(2),
	// Magic Attack
	WARRIOR_MAGIC_ATTACK(2),
	// Armor
	WARRIOR_ARMOR(2),
	// Speed
	WARRIOR_SPEED(2)
))
{
}

CopperHelm::~CopperHelm()
{
}

Item* CopperHelm::clone()
{
	return CopperHelm::create();
}

LocalizedString* CopperHelm::getString()
{
	return Strings::Items_Equipment_Gear_Hats_CopperHelm::create();
}

const std::string& CopperHelm::getIconResource()
{
	return ItemResources::Equipment_Gear_Hats_Tier2_CopperHelm;
}

const std::string& CopperHelm::getIdentifier()
{
	return CopperHelm::SaveKey;
}

Vec2 CopperHelm::getDisplayOffset()
{
	return Vec2(10.0f, -2.0f);
}

Recipe* CopperHelm::getRecipe()
{
	return CopperHelmPlans::create();
}
