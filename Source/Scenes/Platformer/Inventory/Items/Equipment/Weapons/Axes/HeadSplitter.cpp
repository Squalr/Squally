#include "HeadSplitter.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Objects/Platformer/Collectables/IOU.h"

#include "Resources/ObjectResources.h"

#include "Strings/Items/Equipment/Weapons/Axes/HeadSplitter.h"

using namespace cocos2d;

const std::string HeadSplitter::SaveKeyHeadSplitter = "head-splitter";

HeadSplitter* HeadSplitter::create()
{
	HeadSplitter* instance = new HeadSplitter();

	instance->autorelease();

	return instance;
}

HeadSplitter::HeadSplitter() : super(CurrencyInventory::create({{ IOU::getIdentifier(), 2 }}), 4, 7)
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
	return ObjectResources::Items_Equipment_Weapons_Axes_HeadSplitter;
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
