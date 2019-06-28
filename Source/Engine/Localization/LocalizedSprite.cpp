#include "LocalizedSprite.h"

#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCEventListenerCustom.h"

#include "Engine/Events/LocalizationEvents.h"
#include "Engine/Localization/Localization.h"
#include "Engine/Utils/GameUtils.h"
#include "Engine/Utils/StrUtils.h"

using namespace cocos2d;

LocalizedSprite* LocalizedSprite::create(std::string resourceEn)
{
	LocalizedSprite* instance = new LocalizedSprite(resourceEn);

	instance->autorelease();

	return instance;
}

LocalizedSprite::LocalizedSprite(std::string resourceEn)
{
	this->resourceBase = StrUtils::rtrim(resourceEn, Localization::languageTypeToLanguageCode(cocos2d::LanguageType::ENGLISH) + ".png");
	this->localizedSprite = Sprite::create();

	this->updateSprite();

	this->addChild(this->localizedSprite);
}

LocalizedSprite::~LocalizedSprite()
{
}

void LocalizedSprite::onEnter()
{
	super::onEnter();
}

void LocalizedSprite::initializeListeners()
{
	super::initializeListeners();

	this->addEventListenerIgnorePause(EventListenerCustom::create(LocalizationEvents::LocaleChangeEvent, [=](EventCustom* args)
	{
		this->updateSprite();
	}));
}

void LocalizedSprite::updateSprite()
{
	this->localizedSprite->setTexture(this->resourceBase + Localization::languageTypeToLanguageCode(Localization::getLanguage()) + ".png");
}
