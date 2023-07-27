#include "DeveloperModeController.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/base/CCDirector.h"
#include "cocos/base/CCInputEvents.h"

#include "Engine/Events/DeveloperModeEvents.h"
#include "Engine/GlobalDirector.h"
#include "Engine/Localization/Localization.h"
#include "Engine/Utils/MathUtils.h"

using namespace cocos2d;

DeveloperModeController* DeveloperModeController::Instance = nullptr;
volatile bool DeveloperModeController::IsDeveloperBuild = true;
int DeveloperModeController::MaxDebugLevel = 2;
int DeveloperModeController::CurrentDebugLevel = 0;

void DeveloperModeController::RegisterGlobalNode()
{
	if (DeveloperModeController::Instance == nullptr)
	{
		// Register this class globally so that it can always listen for events
		GlobalDirector::getInstance()->RegisterGlobalNode(DeveloperModeController::getInstance());
	}
}

DeveloperModeController* DeveloperModeController::getInstance()
{
	if (DeveloperModeController::Instance == nullptr)
	{
		DeveloperModeController::Instance = new DeveloperModeController();

		DeveloperModeController::Instance->autorelease();
	}

	return DeveloperModeController::Instance;
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
}

void DeveloperModeController::initializeListeners()
{
	super::initializeListeners();

	static LanguageType nextLanguage = LanguageType::ENGLISH;

	this->whenKeyPressed({ InputEvents::KeyCode::KEY_BACK_SLASH }, [=](InputEvents::KeyboardEventArgs* args)
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

	this->whenKeyPressed({ InputEvents::KeyCode::KEY_F1 }, [=](InputEvents::KeyboardEventArgs* args)
	{
		if (!DeveloperModeController::IsDeveloperBuild)
		{
			return;
		}
		
		args->handle();

		this->stopAllActions();
	});

	this->whenKeyPressed({ InputEvents::KeyCode::KEY_F2 }, [=](InputEvents::KeyboardEventArgs* args)
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

	this->whenKeyPressed({ InputEvents::KeyCode::KEY_F3 }, [=](InputEvents::KeyboardEventArgs* args)
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

	this->whenKeyPressed({ InputEvents::KeyCode::KEY_F4 }, [=](InputEvents::KeyboardEventArgs* args)
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

	this->whenKeyPressed({ InputEvents::KeyCode::KEY_F5 }, [=](InputEvents::KeyboardEventArgs* args)
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
