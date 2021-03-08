#include "Tiara.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Tiara::SaveKey = "tiara";

Tiara* Tiara::create()
{
	Tiara* instance = new Tiara();

	instance->autorelease();

	return instance;
}

Tiara::Tiara() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}), ItemStats(
	// Health
	0,
	// Mana
	0,
	// Attack
	0,
	// Magic Attack
	0,
	// Armor
	0,
	// Speed
	0.05f
))
{
}

Tiara::~Tiara()
{
}

Item* Tiara::clone()
{
	return Tiara::create();
}

const std::string& Tiara::getItemName()
{
	return Tiara::SaveKey;
}

LocalizedString* Tiara::getString()
{
	return Strings::Items_Equipment_Gear_Hats_Tiara::create();
}

const std::string& Tiara::getIconResource()
{
	return ItemResources::Equipment_Gear_Hats_Tiara;
}

const std::string& Tiara::getSerializationKey()
{
	return Tiara::SaveKey;
}

Vec2 Tiara::getDisplayOffset()
{
	return Vec2(54.0f, -44.0f);
}
