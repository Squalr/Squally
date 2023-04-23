#include "StrongChitin.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string StrongChitin::SaveKey = "strong-chitin";

StrongChitin* StrongChitin::create()
{
	StrongChitin* instance = new StrongChitin();

	instance->autorelease();

	return instance;
}

StrongChitin::StrongChitin() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 43 }}), ItemMeta(20000))
{
}

StrongChitin::~StrongChitin()
{
}

Item* StrongChitin::clone()
{
	return StrongChitin::create();
}

LocalizedString* StrongChitin::getString()
{
	return Strings::Items_Crafting_BombReagents_StrongChitin::create();
}

const std::string& StrongChitin::getIconResource()
{
	return ItemResources::Crafting_Alchemy_Bombs_T3_StrongChitin;
}

const std::string& StrongChitin::getIdentifier()
{
	return StrongChitin::SaveKey;
}
