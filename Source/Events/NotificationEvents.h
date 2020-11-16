#pragma once
#include <functional>
#include <string>
#include <vector>

class LocalizedString;

class NotificationEvents
{
public:
	static const std::string EventNotificationTakeover;
	static const std::string EventNotification;
	static const std::string EventConfirmation;
	static const std::string EventConfirmationEnd;

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
		bool keepOpen;

		NotificationArgs(LocalizedString* title, LocalizedString* description, std::string iconResource, std::string soundResource, bool keepOpen = false)
			: title(title), description(description), iconResource(iconResource), soundResource(soundResource), keepOpen(keepOpen)
		{
		}
	};

	struct ConfirmationArgs
	{
		LocalizedString* confirmationMessage;
		std::function<bool()> confirmCallback;
		std::function<bool()> cancelCallback;

		ConfirmationArgs(LocalizedString* confirmationMessage, std::function<bool()> confirmCallback, std::function<bool()> cancelCallback = nullptr)
			: confirmationMessage(confirmationMessage), confirmCallback(confirmCallback), cancelCallback(cancelCallback)
		{
		}
	};

	static void TriggerNotificationTakeover(NotificationTakeoverArgs args);
	static void TriggerNotification(NotificationArgs args);
	static void TriggerConfirmation(ConfirmationArgs args);
	static void TriggerConfirmationEnd();
};
