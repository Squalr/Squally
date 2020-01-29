#include "Harbinger.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"

#include "Resources/ObjectResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Harbinger::SaveKeyHarbinger = "harbinger";

Harbinger* Harbinger::create()
{
	Harbinger* instance = new Harbinger();

	instance->autorelease();

	return instance;
}

Harbinger::Harbinger() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}), 3, 6, ItemStats(
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

Harbinger::~Harbinger()
{
}

Item* Harbinger::clone()
{
	return Harbinger::create();
}

std::string Harbinger::getItemName()
{
	return Harbinger::SaveKeyHarbinger;
}

LocalizedString* Harbinger::getString()
{
	return Strings::Items_Equipment_Weapons_Swords_Harbinger::create();
}

std::string Harbinger::getIconResource()
{
	return ObjectResources::Items_Equipment_Weapons_Swords_Harbinger;
}

std::string Harbinger::getSerializationKey()
{
	return Harbinger::SaveKeyHarbinger;
}
