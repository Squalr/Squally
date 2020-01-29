#include "Cleaver.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"

#include "Resources/ObjectResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Cleaver::SaveKeyCleaver = "cleaver";

Cleaver* Cleaver::create()
{
	Cleaver* instance = new Cleaver();

	instance->autorelease();

	return instance;
}

Cleaver::Cleaver() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}), 3, 6, ItemStats(
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

Cleaver::~Cleaver()
{
}

Item* Cleaver::clone()
{
	return Cleaver::create();
}

std::string Cleaver::getItemName()
{
	return Cleaver::SaveKeyCleaver;
}

LocalizedString* Cleaver::getString()
{
	return Strings::Items_Equipment_Weapons_Swords_Cleaver::create();
}

std::string Cleaver::getIconResource()
{
	return ObjectResources::Items_Equipment_Weapons_Swords_Cleaver;
}

std::string Cleaver::getSerializationKey()
{
	return Cleaver::SaveKeyCleaver;
}
