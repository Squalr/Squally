#include "GunpowderT2.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string GunpowderT2::SaveKey = "gun-powder-t2";

GunpowderT2* GunpowderT2::create()
{
	GunpowderT2* instance = new GunpowderT2();

	instance->autorelease();

	return instance;
}

GunpowderT2::GunpowderT2() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 4 }}), ItemMeta(20000))
{
}

GunpowderT2::~GunpowderT2()
{
}

Item* GunpowderT2::clone()
{
	return GunpowderT2::create();
}

LocalizedString* GunpowderT2::getString()
{
	return Strings::Items_Crafting_BombReagents_GunpowderT2::create();
}

const std::string& GunpowderT2::getIconResource()
{
	return ItemResources::Crafting_Alchemy_Bombs_T2_Gunpowder;
}

const std::string& GunpowderT2::getIdentifier()
{
	return GunpowderT2::SaveKey;
}
