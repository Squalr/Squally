#include "GoldenMace.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string GoldenMace::SaveKeyGoldenMace = "golden-mace";

GoldenMace* GoldenMace::create()
{
	GoldenMace* instance = new GoldenMace();

	instance->autorelease();

	return instance;
}

GoldenMace::GoldenMace() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}), 32, 40, ItemStats(
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

GoldenMace::~GoldenMace()
{
}

Item* GoldenMace::clone()
{
	return GoldenMace::create();
}

std::string GoldenMace::getItemName()
{
	return GoldenMace::SaveKeyGoldenMace;
}

LocalizedString* GoldenMace::getString()
{
	return Strings::Items_Equipment_Weapons_Maces_GoldenMace::create();
}

std::string GoldenMace::getIconResource()
{
	return ItemResources::Equipment_Weapons_Maces_GoldenMace;
}

std::string GoldenMace::getSerializationKey()
{
	return GoldenMace::SaveKeyGoldenMace;
}

Vec2 GoldenMace::getDisplayOffset()
{
	return Vec2(0.0f, -24.0f);
}
