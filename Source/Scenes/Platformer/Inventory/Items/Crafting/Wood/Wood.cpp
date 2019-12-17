#include "Wood.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Objects/Platformer/Collectables/IOU.h"

#include "Resources/ObjectResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Wood::SaveKeyWood = "wood";

Wood* Wood::create()
{
	Wood* instance = new Wood();

	instance->autorelease();

	return instance;
}

Wood::Wood() : super(CurrencyInventory::create({{ IOU::getIdentifier(), 1 }}))
{
}

Wood::~Wood()
{
}

Item* Wood::clone()
{
	return Wood::create();
}

std::string Wood::getItemName()
{
	return Wood::SaveKeyWood;
}

LocalizedString* Wood::getString()
{
	return Strings::Items_Crafting_Wood_Wood::create();
}

std::string Wood::getIconResource()
{
	return ObjectResources::Items_Reagents_Wood_Wood;
}

std::string Wood::getSerializationKey()
{
	return Wood::SaveKeyWood;
}
