#include "SpecialReturnToHand.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Hexus/CardData/CardKeys.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string SpecialReturnToHand::SaveKey = "special-return-to-hand";

SpecialReturnToHand* SpecialReturnToHand::create()
{
	SpecialReturnToHand* instance = new SpecialReturnToHand();

	instance->autorelease();

	return instance;
}

SpecialReturnToHand::SpecialReturnToHand() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 14 }}), ItemMeta(3, 3))
{
}

SpecialReturnToHand::~SpecialReturnToHand()
{
}

Item* SpecialReturnToHand::clone()
{
	return SpecialReturnToHand::create();
}

LocalizedString* SpecialReturnToHand::getString()
{
	return Strings::Hexus_Cards_ReturnToHand::create();
}

const std::string& SpecialReturnToHand::getIconResource()
{
	return ItemResources::Collectables_Cards_CardSpecial;
}

const std::string& SpecialReturnToHand::getIdentifier()
{
	return SpecialReturnToHand::SaveKey;
}

std::string SpecialReturnToHand::getCardKey()
{
	return CardKeys::Push;
}
