#include "EssenceOfFrost.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Objects/Platformer/Collectables/IOU.h"

#include "Resources/ObjectResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string EssenceOfFrost::SaveKeyEssenceOfFrost = "essence-of-frost";

EssenceOfFrost* EssenceOfFrost::create()
{
	EssenceOfFrost* instance = new EssenceOfFrost();

	instance->autorelease();

	return instance;
}

EssenceOfFrost::EssenceOfFrost() : super(CurrencyInventory::create({{ IOU::getIdentifier(), 1 }}))
{
}

EssenceOfFrost::~EssenceOfFrost()
{
}

Item* EssenceOfFrost::clone()
{
	return EssenceOfFrost::create();
}

std::string EssenceOfFrost::getItemName()
{
	return EssenceOfFrost::SaveKeyEssenceOfFrost;
}

LocalizedString* EssenceOfFrost::getString()
{
	return Strings::Items_Misc_Essences_EssenceOfFrost::create();
}

std::string EssenceOfFrost::getIconResource()
{
	return ObjectResources::Items_Misc_EssenceOfFrost;
}

std::string EssenceOfFrost::getSerializationKey()
{
	return EssenceOfFrost::SaveKeyEssenceOfFrost;
}

