#include "Stone.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Objects/Platformer/Collectables/IOU.h"

#include "Resources/ObjectResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Stone::SaveKeyStone = "stone";

Stone* Stone::create()
{
	Stone* instance = new Stone();

	instance->autorelease();

	return instance;
}

Stone::Stone() : super(CurrencyInventory::create({{ IOU::getIdentifier(), 1 }}))
{
}

Stone::~Stone()
{
}

Item* Stone::clone()
{
	return Stone::create();
}

std::string Stone::getItemName()
{
	return Stone::SaveKeyStone;
}

LocalizedString* Stone::getString()
{
	return Strings::Items_Crafting_Ore_Stone::create();
}

std::string Stone::getIconResource()
{
	return ObjectResources::Items_Reagents_Ores_Stone;
}

std::string Stone::getSerializationKey()
{
	return Stone::SaveKeyStone;
}
