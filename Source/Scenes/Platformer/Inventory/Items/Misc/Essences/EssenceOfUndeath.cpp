#include "EssenceOfUndeath.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Objects/Platformer/Collectables/IOU.h"

#include "Resources/ObjectResources.h"

#include "Strings/Items/Misc/Essences/EssenceOfUndeath.h"

using namespace cocos2d;

const std::string EssenceOfUndeath::SaveKeyEssenceOfUndeath = "essence-of-undeath";

EssenceOfUndeath* EssenceOfUndeath::create()
{
	EssenceOfUndeath* instance = new EssenceOfUndeath();

	instance->autorelease();

	return instance;
}

EssenceOfUndeath::EssenceOfUndeath() : super(CurrencyInventory::create({{ IOU::getIdentifier(), 1 }}))
{
}

EssenceOfUndeath::~EssenceOfUndeath()
{
}

Item* EssenceOfUndeath::clone()
{
	return EssenceOfUndeath::create();
}

std::string EssenceOfUndeath::getItemName()
{
	return EssenceOfUndeath::SaveKeyEssenceOfUndeath;
}

LocalizedString* EssenceOfUndeath::getString()
{
	return Strings::Items_Misc_Essences_EssenceOfUndeath::create();
}

std::string EssenceOfUndeath::getIconResource()
{
	return ObjectResources::Items_Misc_EssenceOfUndeath;
}

std::string EssenceOfUndeath::getSerializationKey()
{
	return EssenceOfUndeath::SaveKeyEssenceOfUndeath;
}

