#include "Katana.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"

#include "Resources/ObjectResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Katana::SaveKeyKatana = "katana";

Katana* Katana::create()
{
	Katana* instance = new Katana();

	instance->autorelease();

	return instance;
}

Katana::Katana() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}), 16, 24, ItemStats(
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

Katana::~Katana()
{
}

Item* Katana::clone()
{
	return Katana::create();
}

std::string Katana::getItemName()
{
	return Katana::SaveKeyKatana;
}

LocalizedString* Katana::getString()
{
	return Strings::Items_Equipment_Weapons_Swords_Katana::create();
}

std::string Katana::getIconResource()
{
	return ObjectResources::Items_Equipment_Weapons_Swords_Katana;
}

std::string Katana::getSerializationKey()
{
	return Katana::SaveKeyKatana;
}
