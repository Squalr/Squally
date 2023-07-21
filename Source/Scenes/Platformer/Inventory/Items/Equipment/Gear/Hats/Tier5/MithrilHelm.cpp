#include "MithrilHelm.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/Inventory/Items/Recipes/Gear/Hats/Tier5/MithrilHelmPlans.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string MithrilHelm::SaveKey = "mithril-helm";

MithrilHelm* MithrilHelm::create()
{
	MithrilHelm* instance = new MithrilHelm();

	instance->autorelease();

	return instance;
}

MithrilHelm::MithrilHelm() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}), ItemStats(
	// Health
	WARRIOR_HP(5),
	// Mana
	WARRIOR_MP(5),
	// Attack
	WARRIOR_ATTACK(5),
	// Magic Attack
	WARRIOR_MAGIC_ATTACK(5),
	// Armor
	WARRIOR_ARMOR(5),
	// Speed
	WARRIOR_SPEED(5)
))
{
}

MithrilHelm::~MithrilHelm()
{
}

Item* MithrilHelm::clone()
{
	return MithrilHelm::create();
}

LocalizedString* MithrilHelm::getString()
{
	return Strings::Items_Equipment_Gear_Hats_MithrilHelm::create();
}

const std::string& MithrilHelm::getIconResource()
{
	return ItemResources::Equipment_Gear_Hats_Tier5_MithrilHelm;
}

const std::string& MithrilHelm::getIdentifier()
{
	return MithrilHelm::SaveKey;
}

Vec2 MithrilHelm::getDisplayOffset()
{
	return Vec2(4.0f, -22.0f);
}

Recipe* MithrilHelm::getRecipe()
{
	return MithrilHelmPlans::create();
}
