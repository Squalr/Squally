#include "VoidWand.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string VoidWand::SaveKeyVoidWand = "void-wand";

VoidWand* VoidWand::create()
{
	VoidWand* instance = new VoidWand();

	instance->autorelease();

	return instance;
}

VoidWand::VoidWand() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}), 24, 28, ItemStats(
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

VoidWand::~VoidWand()
{
}

Item* VoidWand::clone()
{
	return VoidWand::create();
}

std::string VoidWand::getItemName()
{
	return VoidWand::SaveKeyVoidWand;
}

LocalizedString* VoidWand::getString()
{
	return Strings::Items_Equipment_Weapons_Wands_VoidWand::create();
}

std::string VoidWand::getIconResource()
{
	return ItemResources::Equipment_Weapons_Wands_VoidWand;
}

std::string VoidWand::getSerializationKey()
{
	return VoidWand::SaveKeyVoidWand;
}

Vec2 VoidWand::getDisplayOffset()
{
	return Vec2(0.0f, -24.0f);
}
