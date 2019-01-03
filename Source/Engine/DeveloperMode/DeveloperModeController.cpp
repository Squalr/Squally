#include "DeveloperModeController.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
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

	this->addGlobalEventListener(keyboardListener);
}

bool DeveloperModeController::isDeveloperModeEnabled()
{
	return this->developerModeEnabled;
}

void DeveloperModeController::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	static const LanguageType LastLanguageInEnum = LanguageType::VIETNAMESE;
	static LanguageType nextLanguage = LanguageType::ENGLISH;

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
			this->stopAllActions();
			break;
		}
		case EventKeyboard::KeyCode::KEY_F2:
		{
			this->stopAllActions();
			this->runAction(RepeatForever::create(Sequence::create(
				CallFunc::create([=]()
				{
					Localization::setLanguage(nextLanguage);

					nextLanguage = (LanguageType)(((int)nextLanguage + 1) % (int)LastLanguageInEnum);
				}),
				DelayTime::create(1.0f),
				nullptr
			)));
			break;
		}
		case EventKeyboard::KeyCode::KEY_F3:
		{
			this->stopAllActions();
			this->runAction(RepeatForever::create(Sequence::create(
				CallFunc::create([=]()
				{
					Localization::setLanguage(nextLanguage);

					nextLanguage = (LanguageType)(((int)nextLanguage + 1) % (int)LastLanguageInEnum);
				}),
				DelayTime::create(0.75f),
				nullptr
			)));
			break;
		}
		case EventKeyboard::KeyCode::KEY_F4:
		{
			this->stopAllActions();
			this->runAction(RepeatForever::create(Sequence::create(
				CallFunc::create([=]()
				{
					Localization::setLanguage(nextLanguage);

					nextLanguage = (LanguageType)(((int)nextLanguage + 1) % (int)LastLanguageInEnum);
				}),
				DelayTime::create(0.5f),
				nullptr
			)));
			break;
		}
		this->stopAllActions();
		case EventKeyboard::KeyCode::KEY_F5:
		{
			this->stopAllActions();
			this->runAction(RepeatForever::create(Sequence::create(
				CallFunc::create([=]()
				{
					Localization::setLanguage(nextLanguage);

					nextLanguage = (LanguageType)(((int)nextLanguage + 1) % (int)LastLanguageInEnum);
				}),
				DelayTime::create(0.25f),
				nullptr
			)));
			break;
		}
		default:
		{
			break;
		}
	}
}
