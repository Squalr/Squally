#include "Bludgeon.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Bludgeon::SaveKeyBludgeon = "bludgeon";

Bludgeon* Bludgeon::create()
{
	Bludgeon* instance = new Bludgeon();

	instance->autorelease();

	return instance;
}

Bludgeon::Bludgeon() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}), 24, 32, ItemStats(
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

Bludgeon::~Bludgeon()
{
}

Item* Bludgeon::clone()
{
	return Bludgeon::create();
}

std::string Bludgeon::getItemName()
{
	return Bludgeon::SaveKeyBludgeon;
}

LocalizedString* Bludgeon::getString()
{
	return Strings::Items_Equipment_Weapons_Maces_Bludgeon::create();
}

std::string Bludgeon::getIconResource()
{
	return ItemResources::Equipment_Weapons_Special_Bludgeon;
}

std::string Bludgeon::getSerializationKey()
{
	return Bludgeon::SaveKeyBludgeon;
}

Vec2 Bludgeon::getDisplayOffset()
{
	return Vec2(0.0f, -24.0f);
}
