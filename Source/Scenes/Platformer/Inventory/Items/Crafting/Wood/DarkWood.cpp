#include "DarkWood.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Objects/Platformer/Collectables/IOU.h"

#include "Resources/ObjectResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string DarkWood::SaveKeyDarkWood = "dark-wood";

DarkWood* DarkWood::create()
{
	DarkWood* instance = new DarkWood();

	instance->autorelease();

	return instance;
}

DarkWood::DarkWood() : super(CurrencyInventory::create({{ IOU::getIdentifier(), 1 }}))
{
}

DarkWood::~DarkWood()
{
}

Item* DarkWood::clone()
{
	return DarkWood::create();
}

std::string DarkWood::getItemName()
{
	return DarkWood::SaveKeyDarkWood;
}

LocalizedString* DarkWood::getString()
{
	return Strings::Items_Crafting_Wood_DarkWood::create();
}

std::string DarkWood::getIconResource()
{
	return ObjectResources::Items_Reagents_Wood_DarkWood;
}

std::string DarkWood::getSerializationKey()
{
	return DarkWood::SaveKeyDarkWood;
}
