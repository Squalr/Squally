#include "Rapier.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Objects/Platformer/Collectables/IOU.h"

#include "Resources/ObjectResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Rapier::SaveKeyRapier = "rapier";

Rapier* Rapier::create()
{
	Rapier* instance = new Rapier();

	instance->autorelease();

	return instance;
}

Rapier::Rapier() : super(CurrencyInventory::create({{ IOU::getIdentifier(), 2 }}), 3, 6, ItemStats(
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

Rapier::~Rapier()
{
}

Item* Rapier::clone()
{
	return Rapier::create();
}

std::string Rapier::getItemName()
{
	return Rapier::SaveKeyRapier;
}

LocalizedString* Rapier::getString()
{
	return Strings::Items_Equipment_Weapons_Swords_Rapier::create();
}

std::string Rapier::getIconResource()
{
	return ObjectResources::Items_Equipment_Weapons_Swords_Rapier;
}

std::string Rapier::getSerializationKey()
{
	return Rapier::SaveKeyRapier;
}
