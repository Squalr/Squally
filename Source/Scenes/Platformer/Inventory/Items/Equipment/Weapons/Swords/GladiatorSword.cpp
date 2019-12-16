#include "GladiatorSword.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Objects/Platformer/Collectables/IOU.h"

#include "Resources/ObjectResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string GladiatorSword::SaveKeyGladiatorSword = "gladiator-sword";

GladiatorSword* GladiatorSword::create()
{
	GladiatorSword* instance = new GladiatorSword();

	instance->autorelease();

	return instance;
}

GladiatorSword::GladiatorSword() : super(CurrencyInventory::create({{ IOU::getIdentifier(), 2 }}), 3, 6, ItemStats(
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

GladiatorSword::~GladiatorSword()
{
}

Item* GladiatorSword::clone()
{
	return GladiatorSword::create();
}

std::string GladiatorSword::getItemName()
{
	return GladiatorSword::SaveKeyGladiatorSword;
}

LocalizedString* GladiatorSword::getString()
{
	return Strings::Items_Equipment_Weapons_Swords_GladiatorSword::create();
}

std::string GladiatorSword::getIconResource()
{
	return ObjectResources::Items_Equipment_Weapons_Swords_GladiatorSword;
}

std::string GladiatorSword::getSerializationKey()
{
	return GladiatorSword::SaveKeyGladiatorSword;
}
