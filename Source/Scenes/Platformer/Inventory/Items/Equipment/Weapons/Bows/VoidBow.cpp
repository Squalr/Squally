#include "VoidBow.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string VoidBow::SaveKey = "void-bow";

VoidBow* VoidBow::create()
{
	VoidBow* instance = new VoidBow();

	instance->autorelease();

	return instance;
}

VoidBow::VoidBow() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 7 }}), 6, 8, ItemStats(
	// Health
	0,
	// Mana
	0,
	// Attack
	0,
	// Armor
	0,
	// Speed
	0.25f
))
{
}

VoidBow::~VoidBow()
{
}

Item* VoidBow::clone()
{
	return VoidBow::create();
}

std::string VoidBow::getItemName()
{
	return VoidBow::SaveKey;
}

LocalizedString* VoidBow::getString()
{
	return Strings::Items_Equipment_Weapons_Bows_VoidBow::create();
}

std::string VoidBow::getIconResource()
{
	return ItemResources::Equipment_Weapons_Bows_VoidBow;
}

std::string VoidBow::getSerializationKey()
{
	return VoidBow::SaveKey;
}

Vec2 VoidBow::getDisplayOffset()
{
	return Vec2(0.0f, -24.0f);
}
