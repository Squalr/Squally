#include "Turban.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Turban::SaveKeyTurban = "turban";

Turban* Turban::create()
{
	Turban* instance = new Turban();

	instance->autorelease();

	return instance;
}

Turban::Turban() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}), ItemStats(
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

Turban::~Turban()
{
}

Item* Turban::clone()
{
	return Turban::create();
}

std::string Turban::getItemName()
{
	return Turban::SaveKeyTurban;
}

LocalizedString* Turban::getString()
{
	return Strings::Items_Equipment_Gear_Hats_Turban::create();
}

std::string Turban::getIconResource()
{
	return ItemResources::Equipment_Gear_Hats_Turban;
}

std::string Turban::getSerializationKey()
{
	return Turban::SaveKeyTurban;
}

Vec2 Turban::getDisplayOffset()
{
	return Vec2(2.0f, 6.0f);
}
