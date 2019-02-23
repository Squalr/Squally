#include "SantaHat.h"

#include "Resources/ObjectResources.h"

#include "Strings/Items/Equipment/Gear/Hats/SantaHat.h"

using namespace cocos2d;

const std::string SantaHat::SaveKeySantaHat = "santa-hat";

SantaHat* SantaHat::create()
{
	SantaHat* instance = new SantaHat();

	instance->autorelease();

	return instance;
}

SantaHat::SantaHat() : super(4)
{
}

SantaHat::~SantaHat()
{
}

Item* SantaHat::clone()
{
	return SantaHat::create();
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
