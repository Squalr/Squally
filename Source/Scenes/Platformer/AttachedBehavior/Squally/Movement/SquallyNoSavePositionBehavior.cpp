#include "SquallyNoSavePositionBehavior.h"

#include "Entities/Platformer/Squally/Squally.h"
#include "Scenes/Platformer/AttachedBehavior/Squally/Movement/SquallyMovementBehavior.h"

#include "Resources/EntityResources.h"

using namespace cocos2d;

const std::string SquallyNoSavePositionBehavior::MapKeyAttachedBehavior = "no-position-save";

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
		SquallyMovementBehavior* movementBehavior = this->squally->getAttachedBehavior<SquallyMovementBehavior>();

		if (movementBehavior != nullptr)
		{
			movementBehavior->disablePositionSaving();
		}
	}
}

void SquallyNoSavePositionBehavior::onLoad()
{
}
