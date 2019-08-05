#include "NotificationEvents.h"

#include "cocos/base/CCDirector.h"
#include "cocos/base/CCEventDispatcher.h"

using namespace cocos2d;

const std::string NotificationEvents::EventNotificationTakeover = "EVENT_NOTIFICATION_TAKEOVER";
const std::string NotificationEvents::EventNotification = "EVENT_NOTIFICATION";

void NotificationEvents::TriggerNotificationTakeover(NotificationTakeoverArgs args)
{
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(
		NotificationEvents::EventNotificationTakeover,
		&args
	);
}

void NotificationEvents::TriggerNotification(NotificationArgs args)
{
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(
		NotificationEvents::EventNotification,
		&args
	);
}
