#include "TheldarsHelm.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string TheldarsHelm::SaveKey = "theldars-helm";

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
	// Magic Attack
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

const std::string& TheldarsHelm::getItemName()
{
	return TheldarsHelm::SaveKey;
}

LocalizedString* TheldarsHelm::getString()
{
	return Strings::Items_Equipment_Gear_Hats_TheldarsHelm::create();
}

const std::string& TheldarsHelm::getIconResource()
{
	return ItemResources::Equipment_Gear_Hats_TheldarsHelm;
}

const std::string& TheldarsHelm::getIdentifier()
{
	return TheldarsHelm::SaveKey;
}

Vec2 TheldarsHelm::getDisplayOffset()
{
	return Vec2(-2.0f, 26.0f);
}
