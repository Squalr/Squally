#include "DeveloperModeController.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/base/CCDirector.h"
#include "cocos/base/CCEventListenerKeyboard.h"

#include "Engine/Events/DeveloperModeEvents.h"
#include "Engine/Events/InputEvents.h"
#include "Engine/GlobalDirector.h"
#include "Engine/Localization/Localization.h"
#include "Engine/Utils/MathUtils.h"

using namespace cocos2d;

DeveloperModeController* DeveloperModeController::instance = nullptr;
volatile bool DeveloperModeController::IsDeveloperBuild = true;
volatile bool DeveloperModeController::ShowFPSInfo = false;
int DeveloperModeController::MaxDebugLevel = 2;
int DeveloperModeController::CurrentDebugLevel = 0;

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
	DeveloperModeController::CurrentDebugLevel = 0;
}

DeveloperModeController::~DeveloperModeController()
{
}

void DeveloperModeController::onEnter()
{
	super::onEnter();
	
	if (DeveloperModeController::IsDeveloperBuild && DeveloperModeController::ShowFPSInfo)
	{
		Director::getInstance()->setDisplayStats(true);
	}
}

void DeveloperModeController::initializeListeners()
{
	super::initializeListeners();

	static LanguageType nextLanguage = LanguageType::ENGLISH;

	this->whenKeyPressed({ EventKeyboard::KeyCode::KEY_BACK_SLASH }, [=](KeyboardEventArgs* args)
	{
		if (!DeveloperModeController::IsDeveloperBuild)
		{
			return;
		}
		
		args->handle();

		DeveloperModeController::CurrentDebugLevel = MathUtils::wrappingNormalize(DeveloperModeController::CurrentDebugLevel + 1, 0, DeveloperModeController::MaxDebugLevel);

		if (this->isDeveloperModeEnabled())
		{
			DeveloperModeEvents::TriggerDeveloperModeModeEnable(DeveloperModeEvents::DeveloperModeEnableArgs(DeveloperModeController::CurrentDebugLevel));
		}
		else
		{
			DeveloperModeEvents::TriggerDeveloperModeModeDisable();
		}
	});

	this->whenKeyPressed({ EventKeyboard::KeyCode::KEY_F1 }, [=](KeyboardEventArgs* args)
	{
		if (!DeveloperModeController::IsDeveloperBuild)
		{
			return;
		}
		
		args->handle();

		this->stopAllActions();
	});

	this->whenKeyPressed({ EventKeyboard::KeyCode::KEY_F2 }, [=](KeyboardEventArgs* args)
	{
		if (!DeveloperModeController::IsDeveloperBuild)
		{
			return;
		}
		
		args->handle();

		this->stopAllActions();
		this->runAction(RepeatForever::create(Sequence::create(
			CallFunc::create([=]()
			{
				Localization::setLanguage(nextLanguage);

				nextLanguage = (LanguageType)(((int)nextLanguage + 1) % (int)LanguageType::LAST_LANGUAGE);
			}),
			DelayTime::create(1.0f),
			nullptr
		)));
	});

	this->whenKeyPressed({ EventKeyboard::KeyCode::KEY_F3 }, [=](KeyboardEventArgs* args)
	{
		if (!DeveloperModeController::IsDeveloperBuild)
		{
			return;
		}
		
		args->handle();

		this->stopAllActions();
		this->runAction(RepeatForever::create(Sequence::create(
			CallFunc::create([=]()
			{
				Localization::setLanguage(nextLanguage);

				nextLanguage = (LanguageType)(((int)nextLanguage + 1) % (int)LanguageType::LAST_LANGUAGE);
			}),
			DelayTime::create(0.75f),
			nullptr
		)));
	});

	this->whenKeyPressed({ EventKeyboard::KeyCode::KEY_F4 }, [=](KeyboardEventArgs* args)
	{
		if (!DeveloperModeController::IsDeveloperBuild)
		{
			return;
		}
		
		args->handle();

		this->stopAllActions();
		this->runAction(RepeatForever::create(Sequence::create(
			CallFunc::create([=]()
			{
				Localization::setLanguage(nextLanguage);

				nextLanguage = (LanguageType)(((int)nextLanguage + 1) % (int)LanguageType::LAST_LANGUAGE);
			}),
			DelayTime::create(0.5f),
			nullptr
		)));
	});

	this->whenKeyPressed({ EventKeyboard::KeyCode::KEY_F5 }, [=](KeyboardEventArgs* args)
	{
		if (!DeveloperModeController::IsDeveloperBuild)
		{
			return;
		}
		
		args->handle();

		this->stopAllActions();
		this->runAction(RepeatForever::create(Sequence::create(
			CallFunc::create([=]()
			{
				Localization::setLanguage(nextLanguage);

				nextLanguage = (LanguageType)(((int)nextLanguage + 1) % (int)LanguageType::LAST_LANGUAGE);
			}),
			DelayTime::create(0.25f),
			nullptr
		)));
	});
}

bool DeveloperModeController::isDeveloperModeEnabled()
{
	return DeveloperModeController::CurrentDebugLevel > 0 && DeveloperModeController::CurrentDebugLevel <= DeveloperModeController::MaxDebugLevel;
}

int DeveloperModeController::getDebugLevel()
{
	return DeveloperModeController::CurrentDebugLevel;
}
