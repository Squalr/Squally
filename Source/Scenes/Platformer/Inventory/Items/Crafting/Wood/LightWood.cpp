#include "LightWood.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string LightWood::SaveKey = "light-wood";

LightWood* LightWood::create()
{
	LightWood* instance = new LightWood();

	instance->autorelease();

	return instance;
}

LightWood::LightWood() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 1 }}), ItemMeta(20000))
{
}

LightWood::~LightWood()
{
}

Item* LightWood::clone()
{
	return LightWood::create();
}

LocalizedString* LightWood::getString()
{
	return Strings::Items_Crafting_Wood_LightWood::create();
}

const std::string& LightWood::getIconResource()
{
	return ItemResources::Crafting_Smithing_WoodLight;
}

const std::string& LightWood::getIdentifier()
{
	return LightWood::SaveKey;
}
