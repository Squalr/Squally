#include "GunpowderT3.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string GunpowderT3::SaveKey = "gun-powder-t3";

GunpowderT3* GunpowderT3::create()
{
	GunpowderT3* instance = new GunpowderT3();

	instance->autorelease();

	return instance;
}

GunpowderT3::GunpowderT3() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 6 }}), ItemMeta(20000))
{
}

GunpowderT3::~GunpowderT3()
{
}

Item* GunpowderT3::clone()
{
	return GunpowderT3::create();
}

LocalizedString* GunpowderT3::getString()
{
	return Strings::Items_Crafting_BombReagents_GunpowderT3::create();
}

const std::string& GunpowderT3::getIconResource()
{
	return ItemResources::Crafting_Alchemy_Bombs_T3_Gunpowder;
}

const std::string& GunpowderT3::getIdentifier()
{
	return GunpowderT3::SaveKey;
}
