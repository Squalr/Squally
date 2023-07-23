#include "NecrobatHelm.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/Recipes/Gear/Hats/Tier5/NecrobatHelmPlans.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string NecrobatHelm::SaveKey = "necrobat-helm";

NecrobatHelm* NecrobatHelm::create()
{
	NecrobatHelm* instance = new NecrobatHelm();

	instance->autorelease();

	return instance;
}

NecrobatHelm::NecrobatHelm() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}), ItemStats(
	// Health
	ARCHER_HP(5),
	// Mana
	ARCHER_MP(5),
	// Attack
	ARCHER_ATTACK(5),
	// Magic Attack
	ARCHER_MAGIC_ATTACK(5),
	// Armor
	ARCHER_ARMOR(5),
	// Speed
	ARCHER_SPEED(5)
))
{
}

NecrobatHelm::~NecrobatHelm()
{
}

Item* NecrobatHelm::clone()
{
	return NecrobatHelm::create();
}

LocalizedString* NecrobatHelm::getString()
{
	return Strings::Items_Equipment_Gear_Hats_NecrobatHelm::create();
}

const std::string& NecrobatHelm::getIconResource()
{
	return ItemResources::Equipment_Gear_Hats_Tier5_NecrobatHelm;
}

const std::string& NecrobatHelm::getIdentifier()
{
	return NecrobatHelm::SaveKey;
}

Vec2 NecrobatHelm::getDisplayOffset()
{
	return Vec2(-42.0f, 22.0f);
}

Recipe* NecrobatHelm::getRecipe()
{
	return NecrobatHelmPlans::create();
}
