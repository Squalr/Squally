#include "AttachedBehavior.h"

#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"
#include "cocos/base/CCValue.h"

using namespace cocos2d;

AttachedBehavior::AttachedBehavior(GameObject* owner, std::string attachedBehaviorArgs) : super()
{
	this->attachedBehaviorArgs = attachedBehaviorArgs;
}

AttachedBehavior::~AttachedBehavior()
{
	this->isInvalidated = false;
}

void AttachedBehavior::onEnterTransitionDidFinish()
{
	super::onEnterTransitionDidFinish();

	if (!this->isInvalidated)
	{
		this->onLoad();
	}
}

void AttachedBehavior::initializeListeners()
{
	super::initializeListeners();
}

std::string AttachedBehavior::getAttachedBehaviorArgs()
{
	return this->attachedBehaviorArgs;
}

void AttachedBehavior::invalidate()
{
	this->isInvalidated = true;
}
