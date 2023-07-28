#include "ClickableHackNode.h"

#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"

#include "Engine/Events/HackableEvents.h"
#include "Engine/Utils/GameUtils.h"

#include "Resources/UIResources.h"

using namespace cocos2d;

ClickableHackNode* ClickableHackNode::create(std::string resource, std::string resourceSelected)
{
	ClickableHackNode* instance = new ClickableHackNode(resource, resourceSelected);

	instance->autorelease();

	return instance;
}

ClickableHackNode::ClickableHackNode(std::string resource, std::string resourceSelected)
	: ClickableNode(Sprite::create(resource), Sprite::create(resourceSelected))
{
}

ClickableHackNode::~ClickableHackNode()
{
}

void ClickableHackNode::addEventListener(cocos2d::EventListenerCustom* listener)
{
	static bool isWrappingCall = false;

	if (!isWrappingCall)
	{
		isWrappingCall = true;

		// Pass 'addEventListener' calls to 'addEventListenerIgnorePause', as this button should be clickable no matter what.
		this->addEventListenerIgnorePause(listener);

		isWrappingCall = false;
	}
	else
	{
		super::addEventListener(listener);
	}
}

void ClickableHackNode::initializeListeners()
{
	super::initializeListeners();

	this->addEventListenerIgnorePause(EventListenerCustom::create(HackableEvents::EventHackerModeEnable, [=](EventCustom* eventCustom)
	{
		this->enableInteraction();
	}));

	this->addEventListenerIgnorePause(EventListenerCustom::create(HackableEvents::EventHackableObjectOpen, [=](EventCustom* eventCustom)
	{
		this->disableInteraction();
	}));

	this->addEventListenerIgnorePause(EventListenerCustom::create(HackableEvents::EventHackableObjectClose, [=](EventCustom* eventCustom)
	{
		this->enableInteraction();
	}));
}
