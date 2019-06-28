#include "Doubloons.h"

#include "Resources/ObjectResources.h"

#include "Strings/Items/Currency/Doubloons.h"

using namespace cocos2d;

std::string Doubloons::getIdentifier()
{
	return "Doubloons";
}

std::string Doubloons::getIconResource()
{
	return ObjectResources::Collectables_Doubloon_Doubloon_0000;
}

LocalizedString* Doubloons::getString()
{
	return Strings::Items_Currency_Doubloons::create();
}
