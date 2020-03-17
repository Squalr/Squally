#include "HeadSplitter.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string HeadSplitter::SaveKeyHeadSplitter = "head-splitter";

HeadSplitter* HeadSplitter::create()
{
	HeadSplitter* instance = new HeadSplitter();

	instance->autorelease();

	return instance;
}

HeadSplitter::HeadSplitter() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}), 4, 7, ItemStats(
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

HeadSplitter::~HeadSplitter()
{
}

Item* HeadSplitter::clone()
{
	return HeadSplitter::create();
}

std::string HeadSplitter::getItemName()
{
	return HeadSplitter::SaveKeyHeadSplitter;
}

LocalizedString* HeadSplitter::getString()
{
	return Strings::Items_Equipment_Weapons_Axes_HeadSplitter::create();
}

std::string HeadSplitter::getIconResource()
{
	return ItemResources::Equipment_Weapons_Axes_HeadSplitter;
}

std::string HeadSplitter::getSerializationKey()
{
	return HeadSplitter::SaveKeyHeadSplitter;
}

Size HeadSplitter::getWeaponCollisionSize()
{
	// As expected: Weapon width, height
	return Size(112.0f, 96.0f);
}

Vec2 HeadSplitter::getWeaponOffset()
{
	// Unintuitive: x influences y position, y influences x, likely due to initial weapon rotation
	return Vec2(0.0f, 212.0f);
}
