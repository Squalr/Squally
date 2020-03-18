#include "GoldenSword.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string GoldenSword::SaveKeyGoldenSword = "golden-sword";

GoldenSword* GoldenSword::create()
{
	GoldenSword* instance = new GoldenSword();

	instance->autorelease();

	return instance;
}

GoldenSword::GoldenSword() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}), 10, 13, ItemStats(
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

GoldenSword::~GoldenSword()
{
}

Item* GoldenSword::clone()
{
	return GoldenSword::create();
}

std::string GoldenSword::getItemName()
{
	return GoldenSword::SaveKeyGoldenSword;
}

LocalizedString* GoldenSword::getString()
{
	return Strings::Items_Equipment_Weapons_Swords_GoldenSword::create();
}

std::string GoldenSword::getIconResource()
{
	return ItemResources::Equipment_Weapons_Swords_GoldenSword;
}

std::string GoldenSword::getSerializationKey()
{
	return GoldenSword::SaveKeyGoldenSword;
}
