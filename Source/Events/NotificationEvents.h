#pragma once
#include <string>
#include <vector>

#include "cocos/math/CCGeometry.h"

class LocalizedString;
class PlatformerEntity;

class NotificationEvents
{
public:
	static const std::string EventNotificationTakeover;
	static const std::string EventNotification;

	struct NotificationTakeoverArgs
	{
		LocalizedString* title;
		LocalizedString* description;

		NotificationTakeoverArgs(LocalizedString* title, LocalizedString* description) : title(title), description(description)
		{
		}
	};

	struct NotificationArgs
	{
		LocalizedString* title;
		LocalizedString* description;
		std::string iconResource;

		NotificationArgs(LocalizedString* title, LocalizedString* description, std::string iconResource) : title(title), description(description), iconResource(iconResource)
		{
		}
	};

	static void TriggerNotificationTakeover(NotificationTakeoverArgs args);
	static void TriggerNotification(NotificationArgs args);
};
