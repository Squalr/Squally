#include "Silver.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Objects/Platformer/Collectables/IOU.h"

#include "Resources/ObjectResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Silver::SaveKeySilver = "silver";

Silver* Silver::create()
{
	Silver* instance = new Silver();

	instance->autorelease();

	return instance;
}

Silver::Silver() : super(CurrencyInventory::create({{ IOU::getIdentifier(), 1 }}))
{
}

Silver::~Silver()
{
}

Item* Silver::clone()
{
	return Silver::create();
}

std::string Silver::getItemName()
{
	return Silver::SaveKeySilver;
}

LocalizedString* Silver::getString()
{
	return Strings::Items_Crafting_Ore_Silver::create();
}

std::string Silver::getIconResource()
{
	return ObjectResources::Items_Reagents_Ores_Silver;
}

std::string Silver::getSerializationKey()
{
	return Silver::SaveKeySilver;
}
