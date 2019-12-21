#include "EssenceOfWind.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Objects/Platformer/Collectables/IOU.h"

#include "Resources/ObjectResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string EssenceOfWind::SaveKeyEssenceOfWind = "essence-of-wind";

EssenceOfWind* EssenceOfWind::create()
{
	EssenceOfWind* instance = new EssenceOfWind();

	instance->autorelease();

	return instance;
}

EssenceOfWind::EssenceOfWind() : super(CurrencyInventory::create({{ IOU::getIdentifier(), 1 }}))
{
}

EssenceOfWind::~EssenceOfWind()
{
}

Item* EssenceOfWind::clone()
{
	return EssenceOfWind::create();
}

std::string EssenceOfWind::getItemName()
{
	return EssenceOfWind::SaveKeyEssenceOfWind;
}

LocalizedString* EssenceOfWind::getString()
{
	return Strings::Items_Misc_Essences_EssenceOfWind::create();
}

std::string EssenceOfWind::getIconResource()
{
	return ObjectResources::Items_Misc_EssenceOfWind;
}

std::string EssenceOfWind::getSerializationKey()
{
	return EssenceOfWind::SaveKeyEssenceOfWind;
}

