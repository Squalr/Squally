#include "DarkWood.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string DarkWood::SaveKeyDarkWood = "dark-wood";

DarkWood* DarkWood::create()
{
	DarkWood* instance = new DarkWood();

	instance->autorelease();

	return instance;
}

DarkWood::DarkWood() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 1 }}), ItemMeta(20000))
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
	return ItemResources::Crafting_Wood_DarkWood;
}

std::string DarkWood::getSerializationKey()
{
	return DarkWood::SaveKeyDarkWood;
}
