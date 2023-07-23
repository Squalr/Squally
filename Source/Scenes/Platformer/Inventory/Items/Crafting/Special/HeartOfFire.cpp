#include "HeartOfFire.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string HeartOfFire::SaveKey = "heart-of-fire";

HeartOfFire* HeartOfFire::create()
{
	HeartOfFire* instance = new HeartOfFire();

	instance->autorelease();

	return instance;
}

HeartOfFire::HeartOfFire() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 1 }}), ItemMeta(1, 1))
{
}

HeartOfFire::~HeartOfFire()
{
}

Item* HeartOfFire::clone()
{
	return HeartOfFire::create();
}

LocalizedString* HeartOfFire::getString()
{
	return Strings::Items_Crafting_Special_HeartOfFire::create();
}

const std::string& HeartOfFire::getIconResource()
{
	return ItemResources::Crafting_Smithing_HeartOfFire;
}

const std::string& HeartOfFire::getIdentifier()
{
	return HeartOfFire::SaveKey;
}
