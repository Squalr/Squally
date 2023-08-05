#include "GunpowderT6.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string GunpowderT6::SaveKey = "gun-powder-t6";

GunpowderT6* GunpowderT6::create()
{
	GunpowderT6* instance = new GunpowderT6();

	instance->autorelease();

	return instance;
}

GunpowderT6::GunpowderT6() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 12 }}), ItemMeta(20000))
{
}

GunpowderT6::~GunpowderT6()
{
}

Item* GunpowderT6::clone()
{
	return GunpowderT6::create();
}

LocalizedString* GunpowderT6::getString()
{
	return Strings::Items_Crafting_BombReagents_GunpowderT6::create();
}

const std::string& GunpowderT6::getIconResource()
{
	return ItemResources::Crafting_Alchemy_Bombs_T6_Gunpowder;
}

const std::string& GunpowderT6::getIdentifier()
{
	return GunpowderT6::SaveKey;
}
