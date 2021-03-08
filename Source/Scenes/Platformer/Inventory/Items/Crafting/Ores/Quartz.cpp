#include "Quartz.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Quartz::SaveKey = "quartz";

Quartz* Quartz::create()
{
	Quartz* instance = new Quartz();

	instance->autorelease();

	return instance;
}

Quartz::Quartz() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 28 }}), ItemMeta(20000))
{
}

Quartz::~Quartz()
{
}

Item* Quartz::clone()
{
	return Quartz::create();
}

LocalizedString* Quartz::getString()
{
	return Strings::Items_Crafting_Ore_Quartz::create();
}

const std::string& Quartz::getIconResource()
{
	return ItemResources::Crafting_Smithing_Quartz;
}

const std::string& Quartz::getIdentifier()
{
	return Quartz::SaveKey;
}
