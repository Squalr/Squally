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

VoidCrystal::VoidCrystal() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 212 }}), ItemMeta(20000))
{
}

VoidCrystal::~VoidCrystal()
{
}

Item* VoidCrystal::clone()
{
	return VoidCrystal::create();
}

LocalizedString* VoidCrystal::getString()
{
	return Strings::Items_Crafting_Ore_VoidCrystal::create();
}

const std::string& VoidCrystal::getIconResource()
{
	return ItemResources::Crafting_Smithing_VoidCrystal;
}

const std::string& VoidCrystal::getIdentifier()
{
	return VoidCrystal::SaveKey;
}
