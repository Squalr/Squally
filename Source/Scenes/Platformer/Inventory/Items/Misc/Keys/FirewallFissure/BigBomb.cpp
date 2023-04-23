#include "BigBomb.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string BigBomb::SaveKey = "big-bomb";

BigBomb* BigBomb::create()
{
	BigBomb* instance = new BigBomb();

	instance->autorelease();

	return instance;
}

BigBomb::BigBomb() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 1 }}), ItemMeta(1, 1))
{
}

BigBomb::~BigBomb()
{
}

Item* BigBomb::clone()
{
	return BigBomb::create();
}

LocalizedString* BigBomb::getString()
{
	return Strings::Items_Misc_Keys_BigBomb::create();
}

const std::string& BigBomb::getIconResource()
{
	return ItemResources::Keys_Bomb;
}

const std::string& BigBomb::getIdentifier()
{
	return BigBomb::SaveKey;
}

