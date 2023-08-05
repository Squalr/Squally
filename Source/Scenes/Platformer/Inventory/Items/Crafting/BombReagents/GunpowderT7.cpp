#include "GunpowderT7.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string GunpowderT7::SaveKey = "gun-powder-t7";

GunpowderT7* GunpowderT7::create()
{
	GunpowderT7* instance = new GunpowderT7();

	instance->autorelease();

	return instance;
}

GunpowderT7::GunpowderT7() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 14 }}), ItemMeta(20000))
{
}

GunpowderT7::~GunpowderT7()
{
}

Item* GunpowderT7::clone()
{
	return GunpowderT7::create();
}

LocalizedString* GunpowderT7::getString()
{
	return Strings::Items_Crafting_BombReagents_GunpowderT7::create();
}

const std::string& GunpowderT7::getIconResource()
{
	return ItemResources::Crafting_Alchemy_Bombs_T7_Gunpowder;
}

const std::string& GunpowderT7::getIdentifier()
{
	return GunpowderT7::SaveKey;
}
