#include "EssenceOfNature.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Objects/Platformer/Collectables/IOU.h"

#include "Resources/ObjectResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string EssenceOfNature::SaveKeyEssenceOfNature = "essence-of-nature";

EssenceOfNature* EssenceOfNature::create()
{
	EssenceOfNature* instance = new EssenceOfNature();

	instance->autorelease();

	return instance;
}

EssenceOfNature::EssenceOfNature() : super(CurrencyInventory::create({{ IOU::getIdentifier(), 1 }}))
{
}

EssenceOfNature::~EssenceOfNature()
{
}

Item* EssenceOfNature::clone()
{
	return EssenceOfNature::create();
}

std::string EssenceOfNature::getItemName()
{
	return EssenceOfNature::SaveKeyEssenceOfNature;
}

LocalizedString* EssenceOfNature::getString()
{
	return Strings::Items_Misc_Essences_EssenceOfNature::create();
}

std::string EssenceOfNature::getIconResource()
{
	return ObjectResources::Items_Misc_EssenceOfNature;
}

std::string EssenceOfNature::getSerializationKey()
{
	return EssenceOfNature::SaveKeyEssenceOfNature;
}

