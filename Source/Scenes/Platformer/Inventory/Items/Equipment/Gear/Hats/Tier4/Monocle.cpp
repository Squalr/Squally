#include "Monocle.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Monocle::SaveKey = "monocle";

Monocle* Monocle::create()
{
	Monocle* instance = new Monocle();

	instance->autorelease();

	return instance;
}

Monocle::Monocle() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}), ItemStats(
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

Monocle::~Monocle()
{
}

Item* Monocle::clone()
{
	return Monocle::create();
}

const std::string& Monocle::getItemName()
{
	return Monocle::SaveKey;
}

LocalizedString* Monocle::getString()
{
	return Strings::Items_Equipment_Gear_Hats_Monocle::create();
}

const std::string& Monocle::getIconResource()
{
	return ItemResources::Equipment_Gear_Hats_Monocle;
}

const std::string& Monocle::getSerializationKey()
{
	return Monocle::SaveKey;
}

Vec2 Monocle::getDisplayOffset()
{
	return Vec2(68.0f, -94.0f);
}
