#include "GunpowderT5.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string GunpowderT5::SaveKey = "gun-powder-t5";

GunpowderT5* GunpowderT5::create()
{
	GunpowderT5* instance = new GunpowderT5();

	instance->autorelease();

	return instance;
}

GunpowderT5::GunpowderT5() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 10 }}), ItemMeta(20000))
{
}

GunpowderT5::~GunpowderT5()
{
}

Item* GunpowderT5::clone()
{
	return GunpowderT5::create();
}

LocalizedString* GunpowderT5::getString()
{
	return Strings::Items_Crafting_BombReagents_GunpowderT5::create();
}

const std::string& GunpowderT5::getIconResource()
{
	return ItemResources::Crafting_Alchemy_Bombs_T5_Gunpowder;
}

const std::string& GunpowderT5::getIdentifier()
{
	return GunpowderT5::SaveKey;
}
