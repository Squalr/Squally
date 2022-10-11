#include "Crystal.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Crystal::SaveKey = "crystal";

Crystal* Crystal::create()
{
	Crystal* instance = new Crystal();

	instance->autorelease();

	return instance;
}

Crystal::Crystal() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 16 }}), ItemMeta(20000))
{
}

Crystal::~Crystal()
{
}

Item* Crystal::clone()
{
	return Crystal::create();
}

LocalizedString* Crystal::getString()
{
	return Strings::Items_Crafting_Ore_Crystal::create();
}

const std::string& Crystal::getIconResource()
{
	return ItemResources::Crafting_Smithing_Crystal;
}

const std::string& Crystal::getIdentifier()
{
	return Crystal::SaveKey;
}
