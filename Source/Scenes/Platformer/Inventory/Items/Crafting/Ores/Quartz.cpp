#include "Quartz.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Quartz::SaveKeyQuartz = "quartz";

Quartz* Quartz::create()
{
	Quartz* instance = new Quartz();

	instance->autorelease();

	return instance;
}

Quartz::Quartz() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 1 }}), ItemMeta(20000))
{
}

Quartz::~Quartz()
{
}

Item* Quartz::clone()
{
	return Quartz::create();
}

std::string Quartz::getItemName()
{
	return Quartz::SaveKeyQuartz;
}

LocalizedString* Quartz::getString()
{
	return Strings::Items_Crafting_Ore_Quartz::create();
}

std::string Quartz::getIconResource()
{
	return ItemResources::Crafting_Ores_Quartz;
}

std::string Quartz::getSerializationKey()
{
	return Quartz::SaveKeyQuartz;
}
