#include "Component.h"

#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"
#include "cocos/base/CCValue.h"

#include "Engine/Events/ObjectEvents.h"

using namespace cocos2d;

Component::Component(GameObject* owner) : super()
{
	this->owner = owner;
	this->invalidated = false;
	this->queryable = true;

	if (this->owner == nullptr)
	{
		this->invalidate();
	}
}

Component::~Component()
{
}

void Component::onEnterTransitionDidFinish()
{
	super::onEnterTransitionDidFinish();

	if (!this->invalidated)
	{
		this->onLoad();
	}
}

void Component::onDisable()
{
	this->invalidated = true;

	this->unscheduleUpdate();
	this->removeAllListeners();
}

void Component::invalidate()
{
	this->invalidated = true;
}

bool Component::isInvalidated()
{
	return this->invalidated;
}

void Component::toggleQueryable(bool queryable)
{
	this->queryable = queryable;
}

bool Component::isQueryable()
{
	return (this->queryable && !this->invalidated);
}

GameObject* Component::getOwner()
{
	return this->owner;
}
