#include "Iron.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Iron::SaveKey = "iron";

Iron* Iron::create()
{
	Iron* instance = new Iron();

	instance->autorelease();

	return instance;
}

Iron::Iron() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 18 }}), ItemMeta(20000))
{
}

Iron::~Iron()
{
}

Item* Iron::clone()
{
	return Iron::create();
}

const std::string& Iron::getItemName()
{
	return Iron::SaveKey;
}

LocalizedString* Iron::getString()
{
	return Strings::Items_Crafting_Ore_Iron::create();
}

const std::string& Iron::getIconResource()
{
	return ItemResources::Crafting_Smithing_Iron;
}

const std::string& Iron::getSerializationKey()
{
	return Iron::SaveKey;
}
