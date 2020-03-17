#include "GlowingPendant.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string GlowingPendant::SaveKeyGlowingPendant = "glowing-pendant";

GlowingPendant* GlowingPendant::create()
{
	GlowingPendant* instance = new GlowingPendant();

	instance->autorelease();

	return instance;
}

GlowingPendant::GlowingPendant() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}), ItemStats(
	// Health
	4,
	// Mana
	4,
	// Attack
	1,
	// Armor
	0,
	// Speed
	0.05f
))
{
}

GlowingPendant::~GlowingPendant()
{
}

Item* GlowingPendant::clone()
{
	return GlowingPendant::create();
}

std::string GlowingPendant::getItemName()
{
	return GlowingPendant::SaveKeyGlowingPendant;
}

LocalizedString* GlowingPendant::getString()
{
	return Strings::Items_Equipment_Gear_Necklaces_GlowingPendant::create();
}

std::string GlowingPendant::getIconResource()
{
	return ItemResources::Equipment_Gear_Necklaces_GlowingPendant;
}

std::string GlowingPendant::getSerializationKey()
{
	return GlowingPendant::SaveKeyGlowingPendant;
}
