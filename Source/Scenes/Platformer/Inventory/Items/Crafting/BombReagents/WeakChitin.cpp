#include "WeakChitin.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string WeakChitin::SaveKey = "weak-chitin";

WeakChitin* WeakChitin::create()
{
	WeakChitin* instance = new WeakChitin();

	instance->autorelease();

	return instance;
}

WeakChitin::WeakChitin() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 6 }}), ItemMeta(20000))
{
}

WeakChitin::~WeakChitin()
{
}

Item* WeakChitin::clone()
{
	return WeakChitin::create();
}

LocalizedString* WeakChitin::getString()
{
	return Strings::Items_Crafting_BombReagents_WeakChitin::create();
}

const std::string& WeakChitin::getIconResource()
{
	return ItemResources::Crafting_Alchemy_Bombs_T2_WeakChitin;
}

const std::string& WeakChitin::getIdentifier()
{
	return WeakChitin::SaveKey;
}
