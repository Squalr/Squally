#include "GameComponent.h"

#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"
#include "cocos/base/CCValue.h"

#include "Engine/Events/ObjectEvents.h"

using namespace cocos2d;

GameComponent::GameComponent(GameObject* owner) : super()
{
	this->owner = owner;
	this->invalidated = false;
	this->queryable = true;

	if (this->owner == nullptr)
	{
		this->invalidate();
	}
}

GameComponent::~GameComponent()
{
}

void GameComponent::onEnterTransitionDidFinish()
{
	super::onEnterTransitionDidFinish();

	if (!this->invalidated)
	{
		this->onLoad();
	}
}

void GameComponent::onDisable()
{
	this->invalidated = true;

	this->unscheduleUpdate();
	this->removeAllListeners();
}

void GameComponent::invalidate()
{
	this->invalidated = true;
}

bool GameComponent::isInvalidated()
{
	return this->invalidated;
}

void GameComponent::toggleQueryable(bool queryable)
{
	this->queryable = queryable;
}

bool GameComponent::isQueryable()
{
	return (this->queryable && !this->invalidated);
}

GameObject* GameComponent::getOwner()
{
	return this->owner;
}
