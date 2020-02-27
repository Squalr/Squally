#include "SpikedClub.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"

#include "Resources/ObjectResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string SpikedClub::SaveKeySpikedClub = "spiked-club";

SpikedClub* SpikedClub::create()
{
	SpikedClub* instance = new SpikedClub();

	instance->autorelease();

	return instance;
}

SpikedClub::SpikedClub() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}), 8, 11, ItemStats(
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

SpikedClub::~SpikedClub()
{
}

Item* SpikedClub::clone()
{
	return SpikedClub::create();
}

std::string SpikedClub::getItemName()
{
	return SpikedClub::SaveKeySpikedClub;
}

LocalizedString* SpikedClub::getString()
{
	return Strings::Items_Equipment_Weapons_Maces_SpikedClub::create();
}

std::string SpikedClub::getIconResource()
{
	return ObjectResources::Items_Equipment_Weapons_Maces_SpikedClub;
}

std::string SpikedClub::getSerializationKey()
{
	return SpikedClub::SaveKeySpikedClub;
}

Vec2 SpikedClub::getDisplayOffset()
{
	return Vec2(0.0f, -24.0f);
}
