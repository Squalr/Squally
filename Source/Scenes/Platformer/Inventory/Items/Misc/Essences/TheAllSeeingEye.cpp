#include "TheAllSeeingEye.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Objects/Platformer/Collectables/IOU.h"

#include "Resources/ObjectResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string TheAllSeeingEye::SaveKeyTheAllSeeingEye = "the-all-seeing-eye";

TheAllSeeingEye* TheAllSeeingEye::create()
{
	TheAllSeeingEye* instance = new TheAllSeeingEye();

	instance->autorelease();

	return instance;
}

TheAllSeeingEye::TheAllSeeingEye() : super(CurrencyInventory::create({{ IOU::getIdentifier(), 1 }}))
{
}

TheAllSeeingEye::~TheAllSeeingEye()
{
}

Item* TheAllSeeingEye::clone()
{
	return TheAllSeeingEye::create();
}

std::string TheAllSeeingEye::getItemName()
{
	return TheAllSeeingEye::SaveKeyTheAllSeeingEye;
}

LocalizedString* TheAllSeeingEye::getString()
{
	return Strings::Items_Misc_Essences_TheAllSeeingEye::create();
}

std::string TheAllSeeingEye::getIconResource()
{
	return ObjectResources::Items_Misc_EYE;
}

std::string TheAllSeeingEye::getSerializationKey()
{
	return TheAllSeeingEye::SaveKeyTheAllSeeingEye;
}

