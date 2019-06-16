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

	static LanguageType nextLanguage = LanguageType::ENGLISH;

	this->whenKeyPressed({ EventKeyboard::KeyCode::KEY_GRAVE }, [=](InputEvents::InputArgs* args)
	{
		if (!DeveloperModeController::IsDeveloperBuild)
		{
			return;
		}
		
		args->handled = true;

		if (!this->developerModeEnabled)
		{
			DeveloperModeEvents::TriggerDeveloperModeModeEnable();
		}
		else
		{
			DeveloperModeEvents::TriggerDeveloperModeModeDisable();
		}

		this->developerModeEnabled = !this->developerModeEnabled;
	});

	this->whenKeyPressed({ EventKeyboard::KeyCode::KEY_F1 }, [=](InputEvents::InputArgs* args)
	{
		if (!DeveloperModeController::IsDeveloperBuild)
		{
			return;
		}
		
		args->handled = true;

		this->stopAllActions();
	});

	this->whenKeyPressed({ EventKeyboard::KeyCode::KEY_F2 }, [=](InputEvents::InputArgs* args)
	{
		if (!DeveloperModeController::IsDeveloperBuild)
		{
			return;
		}
		
		args->handled = true;

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

	this->whenKeyPressed({ EventKeyboard::KeyCode::KEY_F3 }, [=](InputEvents::InputArgs* args)
	{
		if (!DeveloperModeController::IsDeveloperBuild)
		{
			return;
		}
		
		args->handled = true;

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

	this->whenKeyPressed({ EventKeyboard::KeyCode::KEY_F4 }, [=](InputEvents::InputArgs* args)
	{
		if (!DeveloperModeController::IsDeveloperBuild)
		{
			return;
		}
		
		args->handled = true;

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

	this->whenKeyPressed({ EventKeyboard::KeyCode::KEY_F5 }, [=](InputEvents::InputArgs* args)
	{
		if (!DeveloperModeController::IsDeveloperBuild)
		{
			return;
		}
		
		args->handled = true;

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
	return this->developerModeEnabled;
}
