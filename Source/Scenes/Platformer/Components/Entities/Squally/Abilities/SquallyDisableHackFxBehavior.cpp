#include "SquallyDisableHackFxBehavior.h"

#include "Entities/Platformer/Squally/Squally.h"

using namespace cocos2d;


SquallyDisableHackFxBehavior* SquallyDisableHackFxBehavior::create(GameObject* owner)
{
	SquallyDisableHackFxBehavior* instance = new SquallyDisableHackFxBehavior(owner);

	instance->autorelease();

	return instance;
}

SquallyDisableHackFxBehavior::SquallyDisableHackFxBehavior(GameObject* owner) : super(owner)
{
	this->squally = dynamic_cast<Squally*>(owner);
	
	if (this->squally == nullptr)
	{
		this->invalidate();
	}
	else
	{
		this->squally->toggleAllowFx(false);
	}
}

SquallyDisableHackFxBehavior::~SquallyDisableHackFxBehavior()
{
}

void SquallyDisableHackFxBehavior::onLoad()
{
}

void SquallyDisableHackFxBehavior::onDisable()
{
	super::onDisable();

	if (this->squally != nullptr)
	{
		this->squally->toggleAllowFx(true);
	}
}
