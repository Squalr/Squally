#include "SantaHat.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Objects/Platformer/Collectables/IOU.h"

#include "Resources/ObjectResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string SantaHat::SaveKeySantaHat = "santa-hat";

SantaHat* SantaHat::create()
{
	SantaHat* instance = new SantaHat();

	instance->autorelease();

	return instance;
}

SantaHat::SantaHat() : super(CurrencyInventory::create({{ IOU::getIdentifier(), 2 }}), 4)
{
}

SantaHat::~SantaHat()
{
}

Item* SantaHat::clone()
{
	return SantaHat::create();
}

std::string SantaHat::getItemName()
{
	return SantaHat::SaveKeySantaHat;
}

LocalizedString* SantaHat::getString()
{
	return Strings::Items_Equipment_Gear_Hats_SantaHat::create();
}

std::string SantaHat::getIconResource()
{
	return ObjectResources::Items_Equipment_Gear_Hats_SantaHat;
}

std::string SantaHat::getSerializationKey()
{
	return SantaHat::SaveKeySantaHat;
}

Vec2 SantaHat::getDisplayOffset()
{
	return Vec2(12.0f, -24.0f);
}
