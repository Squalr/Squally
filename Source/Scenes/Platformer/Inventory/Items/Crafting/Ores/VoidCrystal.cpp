#include "VoidCrystal.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string VoidCrystal::SaveKey = "void-crystal";

VoidCrystal* VoidCrystal::create()
{
	VoidCrystal* instance = new VoidCrystal();

	instance->autorelease();

	return instance;
}

VoidCrystal::VoidCrystal() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 1 }}), ItemMeta(20000))
{
}

VoidCrystal::~VoidCrystal()
{
}

Item* VoidCrystal::clone()
{
	return VoidCrystal::create();
}

std::string VoidCrystal::getItemName()
{
	return VoidCrystal::SaveKey;
}

LocalizedString* VoidCrystal::getString()
{
	return Strings::Items_Crafting_Ore_VoidCrystal::create();
}

std::string VoidCrystal::getIconResource()
{
	return ItemResources::Crafting_Smithing_VoidCrystal;
}

std::string VoidCrystal::getSerializationKey()
{
	return VoidCrystal::SaveKey;
}
