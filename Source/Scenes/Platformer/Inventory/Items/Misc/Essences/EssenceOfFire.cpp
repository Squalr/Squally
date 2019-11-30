#include "EssenceOfFire.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Objects/Platformer/Collectables/IOU.h"

#include "Resources/ObjectResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string EssenceOfFire::SaveKeyEssenceOfFire = "essence-of-fire";

EssenceOfFire* EssenceOfFire::create()
{
	EssenceOfFire* instance = new EssenceOfFire();

	instance->autorelease();

	return instance;
}

EssenceOfFire::EssenceOfFire() : super(CurrencyInventory::create({{ IOU::getIdentifier(), 1 }}))
{
}

EssenceOfFire::~EssenceOfFire()
{
}

Item* EssenceOfFire::clone()
{
	return EssenceOfFire::create();
}

std::string EssenceOfFire::getItemName()
{
	return EssenceOfFire::SaveKeyEssenceOfFire;
}

LocalizedString* EssenceOfFire::getString()
{
	return Strings::Items_Misc_Essences_EssenceOfFire::create();
}

std::string EssenceOfFire::getIconResource()
{
	return ObjectResources::Items_Misc_EssenceOfFire;
}

std::string EssenceOfFire::getSerializationKey()
{
	return EssenceOfFire::SaveKeyEssenceOfFire;
}

