#include "Gold.h"

#include "Resources/ObjectResources.h"

#include "Strings/Items/Currency/Gold.h"

using namespace cocos2d;

std::string Gold::getIdentifier()
{
	return "Gold";
}

std::string Gold::getIconResource()
{
	return ObjectResources::Collectables_Doubloon_Doubloon_0000;
}

LocalizedString* Gold::getString()
{
	return Strings::Items_Currency_Gold::create();
}
