#include "ShamanTiara.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string ShamanTiara::SaveKeyShamanTiara = "shaman-tiara";

ShamanTiara* ShamanTiara::create()
{
	ShamanTiara* instance = new ShamanTiara();

	instance->autorelease();

	return instance;
}

ShamanTiara::ShamanTiara() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}), ItemStats(
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

ShamanTiara::~ShamanTiara()
{
}

Item* ShamanTiara::clone()
{
	return ShamanTiara::create();
}

std::string ShamanTiara::getItemName()
{
	return ShamanTiara::SaveKeyShamanTiara;
}

LocalizedString* ShamanTiara::getString()
{
	return Strings::Items_Equipment_Gear_Hats_ShamanTiara::create();
}

std::string ShamanTiara::getIconResource()
{
	return ItemResources::Equipment_Gear_Hats_ShamanTiara;
}

std::string ShamanTiara::getSerializationKey()
{
	return ShamanTiara::SaveKeyShamanTiara;
}

Vec2 ShamanTiara::getDisplayOffset()
{
	return Vec2(8.0f, -10.0f);
}
