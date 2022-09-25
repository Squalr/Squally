#include "TrainTicket.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string TrainTicket::SaveKey = "train-ticket";

TrainTicket* TrainTicket::create()
{
	TrainTicket* instance = new TrainTicket();

	instance->autorelease();

	return instance;
}

TrainTicket::TrainTicket() : super(CurrencyInventory::create({{ IOU::getIOUIdentifier(), 1 }}), ItemMeta(1, 1))
{
}

TrainTicket::~TrainTicket()
{
}

Item* TrainTicket::clone()
{
	return TrainTicket::create();
}

LocalizedString* TrainTicket::getString()
{
	return Strings::Items_Misc_Keys_TrainTicket::create();
}

const std::string& TrainTicket::getIconResource()
{
	return ItemResources::Misc_Ticket;
}

const std::string& TrainTicket::getIdentifier()
{
	return TrainTicket::SaveKey;
}

