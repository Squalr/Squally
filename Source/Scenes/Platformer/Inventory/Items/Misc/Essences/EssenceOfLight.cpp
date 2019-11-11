#include "EssenceOfLight.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Objects/Platformer/Collectables/IOU.h"

#include "Resources/ObjectResources.h"

#include "Strings/Items/Misc/Essences/EssenceOfLight.h"

using namespace cocos2d;

const std::string EssenceOfLight::SaveKeyEssenceOfLight = "essence-of-light";

EssenceOfLight* EssenceOfLight::create()
{
	EssenceOfLight* instance = new EssenceOfLight();

	instance->autorelease();

	return instance;
}

EssenceOfLight::EssenceOfLight() : super(CurrencyInventory::create({{ IOU::getIdentifier(), 1 }}))
{
}

EssenceOfLight::~EssenceOfLight()
{
}

Item* EssenceOfLight::clone()
{
	return EssenceOfLight::create();
}

std::string EssenceOfLight::getItemName()
{
	return EssenceOfLight::SaveKeyEssenceOfLight;
}

LocalizedString* EssenceOfLight::getString()
{
	return Strings::Items_Misc_Essences_EssenceOfLight::create();
}

std::string EssenceOfLight::getIconResource()
{
	return ObjectResources::Items_Misc_EssenceOfLight;
}

std::string EssenceOfLight::getSerializationKey()
{
	return EssenceOfLight::SaveKeyEssenceOfLight;
}

