#include "PhoenixFeather.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string PhoenixFeather::SaveKey = "phoenix-feather";

PhoenixFeather* PhoenixFeather::create()
{
	PhoenixFeather* instance = new PhoenixFeather();

	instance->autorelease();

	return instance;
}

PhoenixFeather::PhoenixFeather() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 43 }}), ItemMeta(20000))
{
}

PhoenixFeather::~PhoenixFeather()
{
}

Item* PhoenixFeather::clone()
{
	return PhoenixFeather::create();
}

LocalizedString* PhoenixFeather::getString()
{
	return Strings::Items_Crafting_Reagents_PhoenixFeather::create();
}

const std::string& PhoenixFeather::getIconResource()
{
	return ItemResources::Crafting_Alchemy_Reagents_PhoenixFeather;
}

const std::string& PhoenixFeather::getIdentifier()
{
	return PhoenixFeather::SaveKey;
}
