#include "ShopEvents.h"

#include "cocos/base/CCDirector.h"
#include "cocos/base/CCEventDispatcher.h"

using namespace cocos2d;

const std::string ShopEvents::EventRequestItemFromPoolPrefix = "EVENT_REQUEST_ITEM_FROM_POOL_";

void ShopEvents::TriggerRequestItem(ItemRequestArgs args)
{
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(
		ShopEvents::EventRequestItemFromPoolPrefix + args.poolName,
		&args
	);
}
