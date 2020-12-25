#include "SquallyFloatBehavior.h"

#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Entities/Platformer/Squally/Squally.h"

#include "Resources/EntityResources.h"

using namespace cocos2d;

SquallyFloatBehavior* SquallyFloatBehavior::create(GameObject* owner)
{
	SquallyFloatBehavior* instance = new SquallyFloatBehavior(owner);

	instance->autorelease();

	return instance;
}

SquallyFloatBehavior::SquallyFloatBehavior(GameObject* owner) : super(owner)
{
	this->squally = static_cast<Squally*>(owner);

	if (this->squally == nullptr)
	{
		this->invalidate();
	}

	this->elapsed = 0.0f;
}

SquallyFloatBehavior::~SquallyFloatBehavior()
{
}

void SquallyFloatBehavior::onLoad()
{
	this->scheduleUpdate();
}

void SquallyFloatBehavior::onDisable()
{
	super::onDisable();
}

void SquallyFloatBehavior::update(float dt)
{
	super::update(dt);

	this->elapsed += dt;
	
	if (this->squally == nullptr)
	{
		return;
	}

	this->squally->getFloatNode()->setPositionY(std::sin(this->elapsed * 1.5f) * 8.0f);
}
