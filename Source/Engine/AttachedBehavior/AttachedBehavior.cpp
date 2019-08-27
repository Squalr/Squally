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

void AttachedBehavior::invalidate()
{
	this->invalidated = true;
}

bool AttachedBehavior::isInvalidated()
{
	return this->invalidated;
}
