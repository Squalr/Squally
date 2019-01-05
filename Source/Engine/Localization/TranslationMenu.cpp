#include "TranslationMenu.h"

#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"
#include "cocos/base/CCEventListenerKeyboard.h"
#include "cocos/base/CCDirector.h"

#include "Engine/Events/LocalizationEvents.h"
#include "Engine/GlobalDirector.h"
#include "Engine/Utils/GameUtils.h"

#include "Resources/UIResources.h"

using namespace cocos2d;

TranslationMenu* TranslationMenu::instance = nullptr;

void TranslationMenu::registerGlobalNode()
{
	if (TranslationMenu::instance == nullptr)
	{
		// Register this class globally so that it can always listen for events
		GlobalDirector::getInstance()->registerGlobalNode(TranslationMenu::getInstance());
	}
}

TranslationMenu* TranslationMenu::getInstance()
{
	if (TranslationMenu::instance == nullptr)
	{
		TranslationMenu::instance = new TranslationMenu();

		TranslationMenu::instance->autorelease();
	}

	return TranslationMenu::instance;
}

TranslationMenu::TranslationMenu()
{
	this->menuBackground = Sprite::create(UIResources::Menus_OptionsMenu_OptionsMenu);

	this->setVisible(false);

	this->addChild(this->menuBackground);
}

TranslationMenu::~TranslationMenu()
{
}

void TranslationMenu::initializePositions()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->menuBackground->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f));
}

void TranslationMenu::initializeListeners()
{
	super::initializeListeners();

	this->addGlobalEventListener(EventListenerCustom::create(LocalizationEvents::TranslationBeginEdit, [=](EventCustom* eventArgs)
	{
		GameUtils::focus(this);
		this->setVisible(true);
	}));
}
