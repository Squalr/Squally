#include "OlympusBow.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string OlympusBow::SaveKeyOlympusBow = "olympus-bow";

OlympusBow* OlympusBow::create()
{
	OlympusBow* instance = new OlympusBow();

	instance->autorelease();

	return instance;
}

OlympusBow::OlympusBow() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}), 56, 64, ItemStats(
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

OlympusBow::~OlympusBow()
{
}

Item* OlympusBow::clone()
{
	return OlympusBow::create();
}

std::string OlympusBow::getItemName()
{
	return OlympusBow::SaveKeyOlympusBow;
}

LocalizedString* OlympusBow::getString()
{
	return Strings::Items_Equipment_Weapons_Bows_OlympusBow::create();
}

std::string OlympusBow::getIconResource()
{
	return ItemResources::Equipment_Weapons_Bows_OlympusBow;
}

std::string OlympusBow::getSerializationKey()
{
	return OlympusBow::SaveKeyOlympusBow;
}

Vec2 OlympusBow::getDisplayOffset()
{
	return Vec2(0.0f, -24.0f);
}
