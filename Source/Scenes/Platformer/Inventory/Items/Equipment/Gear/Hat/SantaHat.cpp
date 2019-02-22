#include "SantaHat.h"

#include "Resources/ObjectResources.h"

using namespace cocos2d;

const std::string SantaHat::SaveKeySantaHat = "santa-hat";

SantaHat* SantaHat::create()
{
	SantaHat* instance = new SantaHat();

	instance->autorelease();

	return instance;
}

SantaHat::SantaHat() : super(nullptr, ObjectResources::Items_Equipment_Gear_Hats_SantaHat, 4)
{
}

SantaHat::~SantaHat()
{
}

std::string SantaHat::getSerializationKey()
{
	return SantaHat::SaveKeySantaHat;
}
