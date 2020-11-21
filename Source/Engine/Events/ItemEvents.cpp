#include "ItemEvents.h"

#include "cocos/base/CCDirector.h"
#include "cocos/base/CCEventDispatcher.h"

using namespace cocos2d;

const std::string ItemEvents::EventRequestItemFromPoolPrefix = "EVENT_REQUEST_ITEM_FROM_POOL_";

void ItemEvents::TriggerRequestItem(ItemRequestArgs args)
{
	Director::getInstance()->getEventDispatcher()->dispatchEvent(
		ItemEvents::EventRequestItemFromPoolPrefix + args.poolName,
		&args
	);
}
