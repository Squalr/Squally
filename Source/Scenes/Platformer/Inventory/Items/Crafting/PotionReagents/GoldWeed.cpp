#include "GoldWeed.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string GoldWeed::SaveKey = "gold-weed";

GoldWeed* GoldWeed::create()
{
	GoldWeed* instance = new GoldWeed();

	instance->autorelease();

	return instance;
}

GoldWeed::GoldWeed() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 15 }}), ItemMeta(20000))
{
}

GoldWeed::~GoldWeed()
{
}

Item* GoldWeed::clone()
{
	return GoldWeed::create();
}

LocalizedString* GoldWeed::getString()
{
	return Strings::Items_Crafting_PotionReagents_GoldWeed::create();
}

const std::string& GoldWeed::getIconResource()
{
	return ItemResources::Crafting_Alchemy_Potions_T4_GoldWeed;
}

const std::string& GoldWeed::getIdentifier()
{
	return GoldWeed::SaveKey;
}
