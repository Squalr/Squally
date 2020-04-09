#include "VoidFlower.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string VoidFlower::SaveKey = "void-flower";

VoidFlower* VoidFlower::create()
{
	VoidFlower* instance = new VoidFlower();

	instance->autorelease();

	return instance;
}

VoidFlower::VoidFlower() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 69 }}), ItemMeta(20000))
{
}

VoidFlower::~VoidFlower()
{
}

Item* VoidFlower::clone()
{
	return VoidFlower::create();
}

std::string VoidFlower::getItemName()
{
	return VoidFlower::SaveKey;
}

LocalizedString* VoidFlower::getString()
{
	return Strings::Items_Crafting_Plants_VoidFlower::create();
}

std::string VoidFlower::getIconResource()
{
	return ItemResources::Crafting_Alchemy_Plants_VoidFlower;
}

std::string VoidFlower::getSerializationKey()
{
	return VoidFlower::SaveKey;
}
