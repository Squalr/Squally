#include "Doubloons.h"

#include "Resources/ObjectResources.h"

#include "Strings/Items/Currency/Doubloons.h"

using namespace cocos2d;

const std::string Doubloons::SaveKeyDoubloons = "Doubloons";

Doubloons* Doubloons::create()
{
	Doubloons* instance = new Doubloons();

	instance->autorelease();

	return instance;
}

Doubloons::Doubloons() : super()
{
}

Doubloons::~Doubloons()
{
}

Item* Doubloons::clone()
{
	return Doubloons::create();
}

LocalizedString* Doubloons::getString()
{
}

std::string Doubloons::getIconResource()
{
	return ObjectResources::Collectables_Doubloon_Doubloon_0000;
}

std::string Doubloons::getSerializationKey()
{
	return Doubloons::SaveKeyDoubloons;
}
