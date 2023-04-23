#include "RatTail.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string RatTail::SaveKey = "rat-tail";

RatTail* RatTail::create()
{
	RatTail* instance = new RatTail();

	instance->autorelease();

	return instance;
}

RatTail::RatTail() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 24 }}), ItemMeta(20000))
{
}

RatTail::~RatTail()
{
}

Item* RatTail::clone()
{
	return RatTail::create();
}

LocalizedString* RatTail::getString()
{
	return Strings::Items_Crafting_PotionReagents_RatTail::create();
}

const std::string& RatTail::getIconResource()
{
	return ItemResources::Crafting_Alchemy_Potions_T4_RatTail;
}

const std::string& RatTail::getIdentifier()
{
	return RatTail::SaveKey;
}
