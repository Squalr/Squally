#include "NotificationEvents.h"

#include "cocos/base/CCDirector.h"
#include "cocos/base/CCEventDispatcher.h"

using namespace cocos2d;

const std::string NotificationEvents::EventNotificationTakeover = "EVENT_NOTIFICATION_TAKEOVER";
const std::string NotificationEvents::EventNotification = "EVENT_NOTIFICATION";
const std::string NotificationEvents::EventConfirmation = "EVENT_NOTIFICATION_CONFIRMATION";
const std::string NotificationEvents::EventConfirmationEnd = "EVENT_NOTIFICATION_CONFIRMATION_END";

void NotificationEvents::TriggerNotificationTakeover(NotificationTakeoverArgs args)
{
	Director::getInstance()->getEventDispatcher()->dispatchEvent(
		NotificationEvents::EventNotificationTakeover,
		&args
	);
}

void NotificationEvents::TriggerNotification(NotificationArgs args)
{
	Director::getInstance()->getEventDispatcher()->dispatchEvent(
		NotificationEvents::EventNotification,
		&args
	);
}

void NotificationEvents::TriggerConfirmation(ConfirmationArgs args)
{
	Director::getInstance()->getEventDispatcher()->dispatchEvent(
		NotificationEvents::EventConfirmation,
		&args
	);
}

void NotificationEvents::TriggerConfirmationEnd()
{
	Director::getInstance()->getEventDispatcher()->dispatchEvent(
		NotificationEvents::EventConfirmationEnd
	);
}
