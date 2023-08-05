#include "GunpowderT1.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string GunpowderT1::SaveKey = "gun-powder-t1";

GunpowderT1* GunpowderT1::create()
{
	GunpowderT1* instance = new GunpowderT1();

	instance->autorelease();

	return instance;
}

GunpowderT1::GunpowderT1() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 2 }}), ItemMeta(20000))
{
}

GunpowderT1::~GunpowderT1()
{
}

Item* GunpowderT1::clone()
{
	return GunpowderT1::create();
}

LocalizedString* GunpowderT1::getString()
{
	return Strings::Items_Crafting_BombReagents_GunpowderT1::create();
}

const std::string& GunpowderT1::getIconResource()
{
	return ItemResources::Crafting_Alchemy_Bombs_T1_Gunpowder;
}

const std::string& GunpowderT1::getIdentifier()
{
	return GunpowderT1::SaveKey;
}
