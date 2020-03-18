#include "Tin.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Tin::SaveKeyTin = "tin";

Tin* Tin::create()
{
	Tin* instance = new Tin();

	instance->autorelease();

	return instance;
}

Tin::Tin() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 1 }}), ItemMeta(20000))
{
}

Tin::~Tin()
{
}

Item* Tin::clone()
{
	return Tin::create();
}

std::string Tin::getItemName()
{
	return Tin::SaveKeyTin;
}

LocalizedString* Tin::getString()
{
	return Strings::Items_Crafting_Ore_Tin::create();
}

std::string Tin::getIconResource()
{
	return ItemResources::Crafting_Smithing_Tin;
}

std::string Tin::getSerializationKey()
{
	return Tin::SaveKeyTin;
}
