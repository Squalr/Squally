#include "HeliumBomb.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string HeliumBomb::SaveKey = "big-bomb";

HeliumBomb* HeliumBomb::create()
{
	HeliumBomb* instance = new HeliumBomb();

	instance->autorelease();

	return instance;
}

HeliumBomb::HeliumBomb() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 1 }}), ItemMeta(1, 1))
{
}

HeliumBomb::~HeliumBomb()
{
}

Item* HeliumBomb::clone()
{
	return HeliumBomb::create();
}

LocalizedString* HeliumBomb::getString()
{
	return Strings::Items_Misc_Keys_HeliumBomb::create();
}

const std::string& HeliumBomb::getIconResource()
{
	return ItemResources::Keys_HeliumBomb;
}

const std::string& HeliumBomb::getIdentifier()
{
	return HeliumBomb::SaveKey;
}

