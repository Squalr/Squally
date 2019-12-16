#include "SerpentWand.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Objects/Platformer/Collectables/IOU.h"

#include "Resources/ObjectResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string SerpentWand::SaveKeySerpentWand = "serpent-wand";

SerpentWand* SerpentWand::create()
{
	SerpentWand* instance = new SerpentWand();

	instance->autorelease();

	return instance;
}

SerpentWand::SerpentWand() : super(CurrencyInventory::create({{ IOU::getIdentifier(), 2 }}), 3, 6, ItemStats(
	// Health
	0,
	// Mana
	0,
	// Attack
	0,
	// Armor
	0,
	// Speed
	0.05f
))
{
}

SerpentWand::~SerpentWand()
{
}

Item* SerpentWand::clone()
{
	return SerpentWand::create();
}

std::string SerpentWand::getItemName()
{
	return SerpentWand::SaveKeySerpentWand;
}

LocalizedString* SerpentWand::getString()
{
	return Strings::Items_Equipment_Weapons_Wands_SerpentWand::create();
}

std::string SerpentWand::getIconResource()
{
	return ObjectResources::Items_Equipment_Weapons_Wands_SerpentWand;
}

std::string SerpentWand::getSerializationKey()
{
	return SerpentWand::SaveKeySerpentWand;
}

Vec2 SerpentWand::getDisplayOffset()
{
	return Vec2(0.0f, -24.0f);
}
