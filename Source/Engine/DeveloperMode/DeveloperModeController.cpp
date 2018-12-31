#include "DeveloperModeController.h"

#include "cocos/base/CCEventListenerKeyboard.h"

#include "Engine/GlobalDirector.h"
#include "Engine/Localization/Localization.h"

using namespace cocos2d;

DeveloperModeController* DeveloperModeController::instance = nullptr;
bool DeveloperModeController::IsDeveloperBuild = true;

void DeveloperModeController::registerGlobalNode()
{
	// Prevent registering this for events for non-developer builds
	if (!DeveloperModeController::IsDeveloperBuild)
	{
		return;
	}

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
	GlobalNode::initializeListeners();

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
		case EventKeyboard::KeyCode::KEY_F1:
		{
			Localization::setLanguage(LanguageType::ENGLISH);
			break;
		}
		case EventKeyboard::KeyCode::KEY_F2:
		{
			Localization::setLanguage(LanguageType::CHINESE_SIMPLIFIED);
			break;
		}
		case EventKeyboard::KeyCode::KEY_F3:
		{
			Localization::setLanguage(LanguageType::JAPANESE);
			break;
		}
		case EventKeyboard::KeyCode::KEY_F4:
		{
			Localization::setLanguage(LanguageType::KOREAN);
			break;
		}
		case EventKeyboard::KeyCode::KEY_F5:
		{
			Localization::setLanguage(LanguageType::FRENCH);
			break;
		}
		case EventKeyboard::KeyCode::KEY_F6:
		{
			Localization::setLanguage(LanguageType::ITALIAN);
			break;
		}
		case EventKeyboard::KeyCode::KEY_F7:
		{
			Localization::setLanguage(LanguageType::GERMAN);
			break;
		}
		case EventKeyboard::KeyCode::KEY_F8:
		{
			Localization::setLanguage(LanguageType::SPANISH);
			break;
		}
		case EventKeyboard::KeyCode::KEY_F9:
		{
			Localization::setLanguage(LanguageType::RUSSIAN);
			break;
		}
		case EventKeyboard::KeyCode::KEY_F10:
		{
			Localization::setLanguage(LanguageType::VIETNAMESE);
			break;
		}
		case EventKeyboard::KeyCode::KEY_F11:
		{
			Localization::setLanguage(LanguageType::SWEDISH);
			break;
		}
		default:
		{
			break;
		}
	}
}
