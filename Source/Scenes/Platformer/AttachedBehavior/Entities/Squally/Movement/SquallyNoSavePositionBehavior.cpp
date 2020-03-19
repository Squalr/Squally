#include "SquallyNoSavePositionBehavior.h"

#include "Entities/Platformer/Squally/Squally.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Squally/Movement/SquallyMovementBehavior.h"

#include "Resources/EntityResources.h"

using namespace cocos2d;

const std::string SquallyNoSavePositionBehavior::MapKey = "no-position-save";

SquallyNoSavePositionBehavior* SquallyNoSavePositionBehavior::create(GameObject* owner)
{
	SquallyNoSavePositionBehavior* instance = new SquallyNoSavePositionBehavior(owner);

	instance->autorelease();

	return instance;
}

SquallyNoSavePositionBehavior::SquallyNoSavePositionBehavior(GameObject* owner) : super(owner)
{
	this->squally = dynamic_cast<Squally*>(owner);

	if (this->squally == nullptr)
	{
		this->invalidate();
	}
}

SquallyNoSavePositionBehavior::~SquallyNoSavePositionBehavior()
{
}

void SquallyNoSavePositionBehavior::onEnter()
{
	super::onEnter();
	
	if (!this->isInvalidated())
	{
		this->squally->watchForAttachedBehavior<SquallyMovementBehavior>([=](SquallyMovementBehavior* movementBehavior)
		{
			movementBehavior->disablePositionSaving();
		});
	}
}

void SquallyNoSavePositionBehavior::onLoad()
{
}

void SquallyNoSavePositionBehavior::onDisable()
{
	super::onDisable();
}
