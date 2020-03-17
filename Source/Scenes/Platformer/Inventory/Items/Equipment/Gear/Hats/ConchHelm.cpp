#include "ConchHelm.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string ConchHelm::SaveKeyConchHelm = "conch-helm";

ConchHelm* ConchHelm::create()
{
	ConchHelm* instance = new ConchHelm();

	instance->autorelease();

	return instance;
}

ConchHelm::ConchHelm() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}), ItemStats(
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

ConchHelm::~ConchHelm()
{
}

Item* ConchHelm::clone()
{
	return ConchHelm::create();
}

std::string ConchHelm::getItemName()
{
	return ConchHelm::SaveKeyConchHelm;
}

LocalizedString* ConchHelm::getString()
{
	return Strings::Items_Equipment_Gear_Hats_ConchHelm::create();
}

std::string ConchHelm::getIconResource()
{
	return ItemResources::Equipment_Gear_Hats_ConchHelm;
}

std::string ConchHelm::getSerializationKey()
{
	return ConchHelm::SaveKeyConchHelm;
}

Vec2 ConchHelm::getDisplayOffset()
{
	return Vec2(4.0f, -6.0f);
}
