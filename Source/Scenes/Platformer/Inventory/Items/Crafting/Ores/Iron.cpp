#include "Iron.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"

#include "Resources/ObjectResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Iron::SaveKeyIron = "iron";

Iron* Iron::create()
{
	Iron* instance = new Iron();

	instance->autorelease();

	return instance;
}

Iron::Iron() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 1 }}), ItemMeta(20000))
{
}

Iron::~Iron()
{
}

Item* Iron::clone()
{
	return Iron::create();
}

std::string Iron::getItemName()
{
	return Iron::SaveKeyIron;
}

LocalizedString* Iron::getString()
{
	return Strings::Items_Crafting_Ore_Iron::create();
}

std::string Iron::getIconResource()
{
	return ObjectResources::Items_Reagents_Ores_Iron;
}

std::string Iron::getSerializationKey()
{
	return Iron::SaveKeyIron;
}
