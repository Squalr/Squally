#include "DepressingWig.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"

#include "Resources/ObjectResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string DepressingWig::SaveKeyDepressingWig = "depressing-wig";

DepressingWig* DepressingWig::create()
{
	DepressingWig* instance = new DepressingWig();

	instance->autorelease();

	return instance;
}

DepressingWig::DepressingWig() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}), ItemStats(
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

DepressingWig::~DepressingWig()
{
}

Item* DepressingWig::clone()
{
	return DepressingWig::create();
}

std::string DepressingWig::getItemName()
{
	return DepressingWig::SaveKeyDepressingWig;
}

LocalizedString* DepressingWig::getString()
{
	return Strings::Items_Equipment_Gear_Hats_DepressingWig::create();
}

std::string DepressingWig::getIconResource()
{
	return ObjectResources::Items_Equipment_Gear_Hats_DepressingWig;
}

std::string DepressingWig::getSerializationKey()
{
	return DepressingWig::SaveKeyDepressingWig;
}

Vec2 DepressingWig::getDisplayOffset()
{
	return Vec2(18.0f, -48.0f);
}
