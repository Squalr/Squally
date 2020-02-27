#include "ArcaneWand.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"

#include "Resources/ObjectResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string ArcaneWand::SaveKeyArcaneWand = "arcane-wand";

ArcaneWand* ArcaneWand::create()
{
	ArcaneWand* instance = new ArcaneWand();

	instance->autorelease();

	return instance;
}

ArcaneWand::ArcaneWand() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}), 16, 20, ItemStats(
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

ArcaneWand::~ArcaneWand()
{
}

Item* ArcaneWand::clone()
{
	return ArcaneWand::create();
}

std::string ArcaneWand::getItemName()
{
	return ArcaneWand::SaveKeyArcaneWand;
}

LocalizedString* ArcaneWand::getString()
{
	return Strings::Items_Equipment_Weapons_Wands_ArcaneWand::create();
}

std::string ArcaneWand::getIconResource()
{
	return ObjectResources::Items_Equipment_Weapons_Wands_ArcaneWand;
}

std::string ArcaneWand::getSerializationKey()
{
	return ArcaneWand::SaveKeyArcaneWand;
}

Vec2 ArcaneWand::getDisplayOffset()
{
	return Vec2(0.0f, -24.0f);
}
