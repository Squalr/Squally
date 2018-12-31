#include "DeveloperModeController.h"

#include "cocos/base/CCEventListenerKeyboard.h"

#include "Engine/GlobalDirector.h"

using namespace cocos2d;

DeveloperModeController* DeveloperModeController::instance = nullptr;

void DeveloperModeController::registerGlobalNode()
{
	if (DeveloperModeController::instance == nullptr)
	{
		// Register this class globally so that it can always listen for events
		GlobalDirector::getInstance()->registerGlobalNode(DeveloperModeController::getInstance());
	}
}

DeveloperModeController* DeveloperModeController::getInstance()
{
	if (DeveloperModeController::instance == nullptr)
	{
		DeveloperModeController::instance = new DeveloperModeController();

		DeveloperModeController::instance->autorelease();
	}

	return DeveloperModeController::instance;
}

DeveloperModeController::DeveloperModeController()
{
	this->developerModeEnabled = false;
}

DeveloperModeController::~DeveloperModeController()
{
}

void DeveloperModeController::initializeListeners()
{
	super::initializeListeners();

	EventListenerKeyboard* keyboardListener = EventListenerKeyboard::create();

	keyboardListener->onKeyPressed = CC_CALLBACK_2(DeveloperModeController::onKeyPressed, this);

	this->addEventListener(keyboardListener);
}

bool DeveloperModeController::isDeveloperModeEnabled()
{
	return this->developerModeEnabled;
}

void DeveloperModeController::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	switch (keyCode)
	{
		case EventKeyboard::KeyCode::KEY_GRAVE:
		{
			if (!this->developerModeEnabled)
			{
				DeveloperModeEvents::TriggerDeveloperModeModeEnable();
			}
			else
			{
				DeveloperModeEvents::TriggerDeveloperModeModeDisable();
			}

			this->developerModeEnabled = !this->developerModeEnabled;

			event->stopPropagation();
			break;
		}
		default:
		{
			break;
		}
	}
}
