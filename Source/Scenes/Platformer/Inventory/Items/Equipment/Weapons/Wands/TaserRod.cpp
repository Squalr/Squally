#include "TaserRod.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Objects/Platformer/Collectables/IOU.h"

#include "Resources/ObjectResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string TaserRod::SaveKeyTaserRod = "taser-rod";

TaserRod* TaserRod::create()
{
	TaserRod* instance = new TaserRod();

	instance->autorelease();

	return instance;
}

TaserRod::TaserRod() : super(CurrencyInventory::create({{ IOU::getIdentifier(), 2 }}), 3, 6)
{
}

TaserRod::~TaserRod()
{
}

Item* TaserRod::clone()
{
	return TaserRod::create();
}

std::string TaserRod::getItemName()
{
	return TaserRod::SaveKeyTaserRod;
}

LocalizedString* TaserRod::getString()
{
	return Strings::Items_Equipment_Weapons_Wands_TaserRod::create();
}

std::string TaserRod::getIconResource()
{
	return ObjectResources::Items_Equipment_Weapons_Wands_TaserRod;
}

std::string TaserRod::getSerializationKey()
{
	return TaserRod::SaveKeyTaserRod;
}

Vec2 TaserRod::getDisplayOffset()
{
	return Vec2(0.0f, -24.0f);
}
