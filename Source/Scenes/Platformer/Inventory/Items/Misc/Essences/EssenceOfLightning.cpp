#include "EssenceOfLightning.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Objects/Platformer/Collectables/IOU.h"

#include "Resources/ObjectResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string EssenceOfLightning::SaveKeyEssenceOfLightning = "essence-of-lightning";

EssenceOfLightning* EssenceOfLightning::create()
{
	EssenceOfLightning* instance = new EssenceOfLightning();

	instance->autorelease();

	return instance;
}

EssenceOfLightning::EssenceOfLightning() : super(CurrencyInventory::create({{ IOU::getIdentifier(), 1 }}))
{
}

EssenceOfLightning::~EssenceOfLightning()
{
}

Item* EssenceOfLightning::clone()
{
	return EssenceOfLightning::create();
}

std::string EssenceOfLightning::getItemName()
{
	return EssenceOfLightning::SaveKeyEssenceOfLightning;
}

LocalizedString* EssenceOfLightning::getString()
{
	return Strings::Items_Misc_Essences_EssenceOfLightning::create();
}

std::string EssenceOfLightning::getIconResource()
{
	return ObjectResources::Items_Misc_EssenceOfLightning;
}

std::string EssenceOfLightning::getSerializationKey()
{
	return EssenceOfLightning::SaveKeyEssenceOfLightning;
}

