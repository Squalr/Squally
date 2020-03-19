#include "DarkWood.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string DarkWood::SaveKey = "dark-wood";

DarkWood* DarkWood::create()
{
	DarkWood* instance = new DarkWood();

	instance->autorelease();

	return instance;
}

DarkWood::DarkWood() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 40 }}), ItemMeta(20000))
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
	return DarkWood::SaveKey;
}

LocalizedString* DarkWood::getString()
{
	return Strings::Items_Crafting_Wood_DarkWood::create();
}

std::string DarkWood::getIconResource()
{
	return ItemResources::Crafting_Smithing_WoodDark;
}

std::string DarkWood::getSerializationKey()
{
	return DarkWood::SaveKey;
}
