#include "ConfirmationHud.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCLayer.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCDirector.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"

#include "Engine/Localization/LocalizedLabel.h"
#include "Engine/Sound/Sound.h"
#include "Engine/Utils/GameUtils.h"
#include "Engine/Utils/MathUtils.h"
#include "Events/NotificationEvents.h"
#include "Menus/Confirmation/ConfirmationMenu.h"

#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

ConfirmationHud* ConfirmationHud::create()
{
	ConfirmationHud* instance = new ConfirmationHud();

	instance->autorelease();

	return instance;
}

ConfirmationHud::ConfirmationHud()
{
	this->confirmationMenu = ConfirmationMenu::create();
	this->contentNode = Node::create();

	this->contentNode->addChild(this->confirmationMenu);
	this->addChild(this->contentNode);
}

ConfirmationHud::~ConfirmationHud()
{
}

void ConfirmationHud::onEnter()
{
	super::onEnter();
}

void ConfirmationHud::initializePositions()
{
	super::initializePositions();
}

void ConfirmationHud::initializeListeners()
{
	super::initializeListeners();

	this->addEventListenerIgnorePause(EventListenerCustom::create(NotificationEvents::EventConfirmation, [=](EventCustom* eventCustom)
	{
		NotificationEvents::ConfirmationArgs* args = static_cast<NotificationEvents::ConfirmationArgs*>(eventCustom->getUserData());
		
		if (args != nullptr)
		{
			this->confirmationMenu->showMessage(args->confirmationMessage, args->confirmCallback, args->cancelCallback);

			GameUtils::resume(this->confirmationMenu);
		}
	}));
}

void ConfirmationHud::pause()
{
	// ignore
}

void ConfirmationHud::onHackerModeEnable()
{
	super::onHackerModeEnable();

	this->contentNode->setVisible(false);
}

void ConfirmationHud::onHackerModeDisable()
{
	super::onHackerModeDisable();

	this->contentNode->setVisible(true);
}

