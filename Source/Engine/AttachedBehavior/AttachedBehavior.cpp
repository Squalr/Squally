#include "AttachedBehavior.h"

#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"
#include "cocos/base/CCValue.h"

#include "Engine/Events/ObjectEvents.h"

using namespace cocos2d;

AttachedBehavior::AttachedBehavior(GameObject* owner) : super()
{
	this->owner = owner;
	this->invalidated = false;

	if (this->owner == nullptr)
	{
		this->invalidate();
	}
}

AttachedBehavior::~AttachedBehavior()
{
}

void AttachedBehavior::onEnterTransitionDidFinish()
{
	super::onEnterTransitionDidFinish();

	if (!this->invalidated)
	{
		this->onLoad();
	}
}

void AttachedBehavior::initializeListeners()
{
	super::initializeListeners();
}

void AttachedBehavior::listenForStateWrite(std::string key, std::function<void(cocos2d::Value)> onWrite)
{
	const std::string eventKey = key + "_" + std::to_string((unsigned long long)(this->owner));

	this->addEventListenerIgnorePause(EventListenerCustom::create(ObjectEvents::EventWriteStatePrefix + eventKey, [=](EventCustom* eventCustom)
	{
		ObjectEvents::StateWriteArgs* args = static_cast<ObjectEvents::StateWriteArgs*>(eventCustom->getUserData());
		
		if (args != nullptr)
		{
			onWrite(args->value);
		}
	}));
}

void AttachedBehavior::invalidate()
{
	this->invalidated = true;
}

bool AttachedBehavior::isInvalidated()
{
	return this->invalidated;
}
