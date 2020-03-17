#include "Stone.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Stone::SaveKeyStone = "stone";

Stone* Stone::create()
{
	Stone* instance = new Stone();

	instance->autorelease();

	return instance;
}

Stone::Stone() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 1 }}), ItemMeta(20000))
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
	return ItemResources::Crafting_Ores_Stone;
}

std::string Stone::getSerializationKey()
{
	return Stone::SaveKeyStone;
}
