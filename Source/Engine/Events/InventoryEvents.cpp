#include "InventoryEvents.h"

#include "cocos/base/CCDirector.h"
#include "cocos/base/CCEventDispatcher.h"

using namespace cocos2d;

const std::string InventoryEvents::EventRequestItemDeserialization = "EVENT_REQUEST_ITEM_DESERIALIZATION";
const std::string InventoryEvents::EventInventoryInstanceChangedPrefix = "EVENT_INVENTORY_INSTANCE_CHANGED_";
const std::string InventoryEvents::EventCurrencyInventoryInstanceChangedPrefix = "EVENT_CURRENCY_INVENTORY_INSTANCE_CHANGED_";

void InventoryEvents::TriggerRequestItemDeserialization(RequestItemDeserializationArgs args)
{
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(
		InventoryEvents::EventRequestItemDeserialization,
		&args
	);
}

void InventoryEvents::TriggerInventoryInstanceChanged(InventoryInstanceChangedArgs args)
{
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(
		InventoryEvents::EventInventoryInstanceChangedPrefix + args.inventorySaveKey,
		&args
	);
}

void InventoryEvents::TriggerCurrencyInventoryInstanceChanged(CurrencyInventoryInstanceChangedArgs args)
{
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(
		InventoryEvents::EventCurrencyInventoryInstanceChangedPrefix + args.inventorySaveKey,
		&args
	);
}
