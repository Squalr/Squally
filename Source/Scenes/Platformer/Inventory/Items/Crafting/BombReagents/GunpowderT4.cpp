#include "GunpowderT4.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string GunpowderT4::SaveKey = "gun-powder-t4";

GunpowderT4* GunpowderT4::create()
{
	GunpowderT4* instance = new GunpowderT4();

	instance->autorelease();

	return instance;
}

GunpowderT4::GunpowderT4() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 8 }}), ItemMeta(20000))
{
}

GunpowderT4::~GunpowderT4()
{
}

Item* GunpowderT4::clone()
{
	return GunpowderT4::create();
}

LocalizedString* GunpowderT4::getString()
{
	return Strings::Items_Crafting_BombReagents_GunpowderT4::create();
}

const std::string& GunpowderT4::getIconResource()
{
	return ItemResources::Crafting_Alchemy_Bombs_T4_Gunpowder;
}

const std::string& GunpowderT4::getIdentifier()
{
	return GunpowderT4::SaveKey;
}
