#include "EmeraldPendant.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string EmeraldPendant::SaveKey = "emerald-pendant";

EmeraldPendant* EmeraldPendant::create()
{
	EmeraldPendant* instance = new EmeraldPendant();

	instance->autorelease();

	return instance;
}

EmeraldPendant::EmeraldPendant() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 22 }}), ItemStats(
	// Health
	3,
	// Mana
	3,
	// Attack
	1,
	// Magic Attack
	1,
	// Armor
	0,
	// Speed
	0.05f
))
{
}

EmeraldPendant::~EmeraldPendant()
{
}

Item* EmeraldPendant::clone()
{
	return EmeraldPendant::create();
}

std::string EmeraldPendant::getItemName()
{
	return EmeraldPendant::SaveKey;
}

LocalizedString* EmeraldPendant::getString()
{
	return Strings::Items_Equipment_Gear_Necklaces_EmeraldPendant::create();
}

std::string EmeraldPendant::getIconResource()
{
	return ItemResources::Equipment_Gear_Necklaces_EmeraldPendant;
}

std::string EmeraldPendant::getSerializationKey()
{
	return EmeraldPendant::SaveKey;
}
