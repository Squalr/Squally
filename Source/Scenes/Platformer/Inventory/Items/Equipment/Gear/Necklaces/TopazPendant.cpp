#include "TopazPendant.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string TopazPendant::SaveKey = "topaz-pendant";

TopazPendant* TopazPendant::create()
{
	TopazPendant* instance = new TopazPendant();

	instance->autorelease();

	return instance;
}

TopazPendant::TopazPendant() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 15 }}), ItemStats(
	// Health
	2,
	// Mana
	2,
	// Attack
	1,
	// Magic Attack
	1,
	// Armor
	0,
	// Speed
	0.05f
))
{
}

TopazPendant::~TopazPendant()
{
}

Item* TopazPendant::clone()
{
	return TopazPendant::create();
}

std::string TopazPendant::getItemName()
{
	return TopazPendant::SaveKey;
}

LocalizedString* TopazPendant::getString()
{
	return Strings::Items_Equipment_Gear_Necklaces_TopazPendant::create();
}

std::string TopazPendant::getIconResource()
{
	return ItemResources::Equipment_Gear_Necklaces_TopazPendant;
}

std::string TopazPendant::getSerializationKey()
{
	return TopazPendant::SaveKey;
}
