#include "SpecialPush.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Hexus/CardData/CardKeys.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string SpecialPush::SaveKey = "special-push";

SpecialPush* SpecialPush::create()
{
	SpecialPush* instance = new SpecialPush();

	instance->autorelease();

	return instance;
}

SpecialPush::SpecialPush() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 19 }}), ItemMeta(3, 3))
{
}

SpecialPush::~SpecialPush()
{
}

Item* SpecialPush::clone()
{
	return SpecialPush::create();
}

LocalizedString* SpecialPush::getString()
{
	return Strings::Hexus_Cards_Push::create();
}

const std::string& SpecialPush::getIconResource()
{
	return ItemResources::Collectables_Cards_CardSpecial;
}

const std::string& SpecialPush::getIdentifier()
{
	return SpecialPush::SaveKey;
}

std::string SpecialPush::getCardKey()
{
	return CardKeys::Push;
}
