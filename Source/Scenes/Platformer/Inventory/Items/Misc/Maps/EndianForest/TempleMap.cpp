#include "TempleMap.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string TempleMap::SaveKey = "temple-map";

TempleMap* TempleMap::create()
{
	TempleMap* instance = new TempleMap();

	instance->autorelease();

	return instance;
}

TempleMap::TempleMap() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 1 }}), ItemMeta(1, 1))
{
}

TempleMap::~TempleMap()
{
}

Item* TempleMap::clone()
{
	return TempleMap::create();
}

const std::string& TempleMap::getItemName()
{
	return TempleMap::SaveKey;
}

LocalizedString* TempleMap::getString()
{
	return Strings::Items_Misc_Maps_DungeonMap::create()
		->setStringReplacementVariables(Strings::Platformer_MapNames_EndianForest_LimestoneTemple::create());
}

const std::string& TempleMap::getIconResource()
{
	return ItemResources::Maps_Map;
}

const std::string& TempleMap::getIdentifier()
{
	return TempleMap::SaveKey;
}

