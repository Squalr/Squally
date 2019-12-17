#include "Quartz.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Objects/Platformer/Collectables/IOU.h"

#include "Resources/ObjectResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Quartz::SaveKeyQuartz = "quartz";

Quartz* Quartz::create()
{
	Quartz* instance = new Quartz();

	instance->autorelease();

	return instance;
}

Quartz::Quartz() : super(CurrencyInventory::create({{ IOU::getIdentifier(), 1 }}))
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
	return ObjectResources::Items_Reagents_Ores_Quartz;
}

std::string Quartz::getSerializationKey()
{
	return Quartz::SaveKeyQuartz;
}
