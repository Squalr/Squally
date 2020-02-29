#include "Monocle.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"

#include "Resources/ObjectResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Monocle::SaveKeyMonocle = "monocle";

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

std::string Monocle::getItemName()
{
	return Monocle::SaveKeyMonocle;
}

LocalizedString* Monocle::getString()
{
	return Strings::Items_Equipment_Gear_Hats_SantaHat::create();
}

std::string Monocle::getIconResource()
{
	return ObjectResources::Items_Equipment_Gear_Hats_Monocle;
}

std::string Monocle::getSerializationKey()
{
	return Monocle::SaveKeyMonocle;
}

Vec2 Monocle::getDisplayOffset()
{
	return Vec2(68.0f, -94.0f);
}
