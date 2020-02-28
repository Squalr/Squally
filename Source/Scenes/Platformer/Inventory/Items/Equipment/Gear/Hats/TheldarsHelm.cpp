#include "TheldarsHelm.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"

#include "Resources/ObjectResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string TheldarsHelm::SaveKeyTheldarsHelm = "theldars-helm";

TheldarsHelm* TheldarsHelm::create()
{
	TheldarsHelm* instance = new TheldarsHelm();

	instance->autorelease();

	return instance;
}

TheldarsHelm::TheldarsHelm() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}), ItemStats(
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

TheldarsHelm::~TheldarsHelm()
{
}

Item* TheldarsHelm::clone()
{
	return TheldarsHelm::create();
}

std::string TheldarsHelm::getItemName()
{
	return TheldarsHelm::SaveKeyTheldarsHelm;
}

LocalizedString* TheldarsHelm::getString()
{
	return Strings::Items_Equipment_Gear_Hats_SantaHat::create();
}

std::string TheldarsHelm::getIconResource()
{
	return ObjectResources::Items_Equipment_Gear_Hats_TheldarsHelm;
}

std::string TheldarsHelm::getSerializationKey()
{
	return TheldarsHelm::SaveKeyTheldarsHelm;
}

Vec2 TheldarsHelm::getDisplayOffset()
{
	return Vec2(12.0f, -24.0f);
}
