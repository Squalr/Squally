#include "Coal.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Objects/Platformer/Collectables/IOU.h"

#include "Resources/ObjectResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Coal::SaveKeyCoal = "coal";

Coal* Coal::create()
{
	Coal* instance = new Coal();

	instance->autorelease();

	return instance;
}

Coal::Coal() : super(CurrencyInventory::create({{ IOU::getIdentifier(), 1 }}))
{
}

Coal::~Coal()
{
}

Item* Coal::clone()
{
	return Coal::create();
}

std::string Coal::getItemName()
{
	return Coal::SaveKeyCoal;
}

LocalizedString* Coal::getString()
{
	return Strings::Items_Crafting_Ore_Coal::create();
}

std::string Coal::getIconResource()
{
	return ObjectResources::Items_Reagents_Ores_Coal;
}

std::string Coal::getSerializationKey()
{
	return Coal::SaveKeyCoal;
}
