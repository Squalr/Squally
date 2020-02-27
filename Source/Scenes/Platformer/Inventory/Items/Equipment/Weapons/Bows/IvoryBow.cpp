#include "IvoryBow.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"

#include "Resources/ObjectResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string IvoryBow::SaveKeyIvoryBow = "ivory-bow";

IvoryBow* IvoryBow::create()
{
	IvoryBow* instance = new IvoryBow();

	instance->autorelease();

	return instance;
}

IvoryBow::IvoryBow() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}), 40, 48, ItemStats(
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

IvoryBow::~IvoryBow()
{
}

Item* IvoryBow::clone()
{
	return IvoryBow::create();
}

std::string IvoryBow::getItemName()
{
	return IvoryBow::SaveKeyIvoryBow;
}

LocalizedString* IvoryBow::getString()
{
	return Strings::Items_Equipment_Weapons_Bows_IvoryBow::create();
}

std::string IvoryBow::getIconResource()
{
	return ObjectResources::Items_Equipment_Weapons_Bows_IvoryBow;
}

std::string IvoryBow::getSerializationKey()
{
	return IvoryBow::SaveKeyIvoryBow;
}

Vec2 IvoryBow::getDisplayOffset()
{
	return Vec2(0.0f, -24.0f);
}
