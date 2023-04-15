#include "HellGateCrystal.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string HellGateCrystal::SaveKey = "hell-gate-key";

HellGateCrystal* HellGateCrystal::create()
{
	HellGateCrystal* instance = new HellGateCrystal();

	instance->autorelease();

	return instance;
}

HellGateCrystal::HellGateCrystal() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 1 }}), ItemMeta(1, 1))
{
}

HellGateCrystal::~HellGateCrystal()
{
}

Item* HellGateCrystal::clone()
{
	return HellGateCrystal::create();
}

LocalizedString* HellGateCrystal::getString()
{
	return Strings::Items_Misc_Keys_HellGateCrystal::create();
}

const std::string& HellGateCrystal::getIconResource()
{
	return ItemResources::Keys_HellGateCrystal;
}

const std::string& HellGateCrystal::getIdentifier()
{
	return HellGateCrystal::SaveKey;
}

