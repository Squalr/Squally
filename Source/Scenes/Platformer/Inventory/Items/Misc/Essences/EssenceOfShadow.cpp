#include "EssenceOfShadow.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Objects/Platformer/Collectables/IOU.h"

#include "Resources/ObjectResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string EssenceOfShadow::SaveKeyEssenceOfShadow = "essence-of-shadow";

EssenceOfShadow* EssenceOfShadow::create()
{
	EssenceOfShadow* instance = new EssenceOfShadow();

	instance->autorelease();

	return instance;
}

EssenceOfShadow::EssenceOfShadow() : super(CurrencyInventory::create({{ IOU::getIdentifier(), 1 }}))
{
}

EssenceOfShadow::~EssenceOfShadow()
{
}

Item* EssenceOfShadow::clone()
{
	return EssenceOfShadow::create();
}

std::string EssenceOfShadow::getItemName()
{
	return EssenceOfShadow::SaveKeyEssenceOfShadow;
}

LocalizedString* EssenceOfShadow::getString()
{
	return Strings::Items_Misc_Essences_EssenceOfShadow::create();
}

std::string EssenceOfShadow::getIconResource()
{
	return ObjectResources::Items_Misc_EssenceOfShadow;
}

std::string EssenceOfShadow::getSerializationKey()
{
	return EssenceOfShadow::SaveKeyEssenceOfShadow;
}

