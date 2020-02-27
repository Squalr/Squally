#include "Impaler.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"

#include "Resources/ObjectResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Impaler::SaveKeyImpaler = "impaler";

Impaler* Impaler::create()
{
	Impaler* instance = new Impaler();

	instance->autorelease();

	return instance;
}

Impaler::Impaler() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}), 32, 40, ItemStats(
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

Impaler::~Impaler()
{
}

Item* Impaler::clone()
{
	return Impaler::create();
}

std::string Impaler::getItemName()
{
	return Impaler::SaveKeyImpaler;
}

LocalizedString* Impaler::getString()
{
	return Strings::Items_Equipment_Weapons_Spears_Impaler::create();
}

std::string Impaler::getIconResource()
{
	return ObjectResources::Items_Equipment_Weapons_Spears_Impaler;
}

std::string Impaler::getSerializationKey()
{
	return Impaler::SaveKeyImpaler;
}

Vec2 Impaler::getDisplayOffset()
{
	return Vec2(0.0f, -24.0f);
}
