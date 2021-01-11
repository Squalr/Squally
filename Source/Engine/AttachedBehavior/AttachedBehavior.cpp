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
	this->queryable = true;

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

void AttachedBehavior::onDisable()
{
	this->invalidated = true;

	this->unscheduleUpdate();
	this->removeAllListeners();
}

void AttachedBehavior::invalidate()
{
	this->invalidated = true;
}

bool AttachedBehavior::isInvalidated()
{
	return this->invalidated;
}

void AttachedBehavior::toggleQueryable(bool queryable)
{
	this->queryable = queryable;
}

bool AttachedBehavior::isQueryable()
{
	return (this->queryable && !this->invalidated);
}

GameObject* AttachedBehavior::getOwner()
{
	return this->owner;
}
