#include "MagesHatRed.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string MagesHatRed::SaveKeyMagesHatRed = "mages-hat-red";

MagesHatRed* MagesHatRed::create()
{
	MagesHatRed* instance = new MagesHatRed();

	instance->autorelease();

	return instance;
}

MagesHatRed::MagesHatRed() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}), ItemStats(
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

MagesHatRed::~MagesHatRed()
{
}

Item* MagesHatRed::clone()
{
	return MagesHatRed::create();
}

std::string MagesHatRed::getItemName()
{
	return MagesHatRed::SaveKeyMagesHatRed;
}

LocalizedString* MagesHatRed::getString()
{
	return Strings::Items_Equipment_Gear_Hats_MagesHatRed::create();
}

std::string MagesHatRed::getIconResource()
{
	return ItemResources::Equipment_Gear_Hats_MagesHatRed;
}

std::string MagesHatRed::getSerializationKey()
{
	return MagesHatRed::SaveKeyMagesHatRed;
}

Vec2 MagesHatRed::getDisplayOffset()
{
	return Vec2(-36.0f, -12.0f);
}
