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
			Localization::setLanguage(LanguageType::THAI);
			break;
		}
		case EventKeyboard::KeyCode::KEY_F6:
		{
			Localization::setLanguage(LanguageType::VIETNAMESE);
			break;
		}
		case EventKeyboard::KeyCode::KEY_F7:
		{
			Localization::setLanguage(LanguageType::RUSSIAN);
			break;
		}
		case EventKeyboard::KeyCode::KEY_F8:
		{
			Localization::setLanguage(LanguageType::UKRAINIAN);
			break;
		}
		case EventKeyboard::KeyCode::KEY_F9:
		{
			Localization::setLanguage(LanguageType::HUNGARIAN);
			break;
		}
		case EventKeyboard::KeyCode::KEY_F10:
		{
			Localization::setLanguage(LanguageType::BULGARIAN);
			break;
		}
		case EventKeyboard::KeyCode::KEY_F11:
		{
			Localization::setLanguage(LanguageType::CZECH);
			break;
		}
		case EventKeyboard::KeyCode::KEY_1:
		{
			Localization::setLanguage(LanguageType::ARABIC);
			break;
		}
		case EventKeyboard::KeyCode::KEY_2:
		{
			Localization::setLanguage(LanguageType::CHINESE_TRADITIONAL);
			break;
		}
		case EventKeyboard::KeyCode::KEY_3:
		{
			Localization::setLanguage(LanguageType::GREEK);
			break;
		}
		case EventKeyboard::KeyCode::KEY_4:
		{
			Localization::setLanguage(LanguageType::DANISH);
			break;
		}
		case EventKeyboard::KeyCode::KEY_5:
		{
			Localization::setLanguage(LanguageType::DUTCH);
			break;
		}
		case EventKeyboard::KeyCode::KEY_6:
		{
			Localization::setLanguage(LanguageType::FINNISH);
			break;
		}
		case EventKeyboard::KeyCode::KEY_7:
		{
			Localization::setLanguage(LanguageType::FRENCH);
			break;
		}
		case EventKeyboard::KeyCode::KEY_9:
		{
			Localization::setLanguage(LanguageType::POLISH);
			break;
		}
		case EventKeyboard::KeyCode::KEY_0:
		{
			Localization::setLanguage(LanguageType::TURKISH);
			break;
		}
		case EventKeyboard::KeyCode::KEY_PG_UP:
		{
			Localization::setLanguage(LanguageType::PORTUGUESE);
			break;
		}
		case EventKeyboard::KeyCode::KEY_EQUAL:
		{
			Localization::setLanguage(LanguageType::PORTUGUESE_BRAZIL);
			break;
		}
		case EventKeyboard::KeyCode::KEY_HOME:
		{
			Localization::setLanguage(LanguageType::SWEDISH);
			break;
		}
		case EventKeyboard::KeyCode::KEY_INSERT:
		{
			Localization::setLanguage(LanguageType::ROMANIAN);
			break;
		}
		default:
		{
			break;
		}
	}
}
