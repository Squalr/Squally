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
		std::string soundResource;

		NotificationTakeoverArgs(LocalizedString* title, LocalizedString* description, std::string soundResource)
			: title(title), description(description), soundResource(soundResource)
		{
		}
	};

	struct NotificationArgs
	{
		LocalizedString* title;
		LocalizedString* description;
		std::string iconResource;
		std::string soundResource;

		NotificationArgs(LocalizedString* title, LocalizedString* description, std::string iconResource, std::string soundResource)
			: title(title), description(description), iconResource(iconResource), soundResource(soundResource)
		{
		}
	};

	static void TriggerNotificationTakeover(NotificationTakeoverArgs args);
	static void TriggerNotification(NotificationArgs args);
};
