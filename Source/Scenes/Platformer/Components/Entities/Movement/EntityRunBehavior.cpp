#include "EntityRunBehavior.h"

#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"
#include "cocos/base/CCValue.h"

#include "Entities/Platformer/PlatformerEntity.h"
#include "Scenes/Platformer/Components/Entities/Movement/EntityMovementBehavior.h"

using namespace cocos2d;

const std::string EntityRunBehavior::MapKey = "run";
const float EntityRunBehavior::RunAcceleration = 11200.0f;

EntityRunBehavior* EntityRunBehavior::create(GameObject* owner)
{
	EntityRunBehavior* instance = new EntityRunBehavior(owner);

	instance->autorelease();

	return instance;
}

EntityRunBehavior::EntityRunBehavior(GameObject* owner) : super(owner)
{
	this->entity = dynamic_cast<PlatformerEntity*>(owner);

	if (this->entity == nullptr)
	{
		this->invalidate();
	}
}

EntityRunBehavior::~EntityRunBehavior()
{
}

void EntityRunBehavior::onLoad()
{
	this->entity->watchForComponent<EntityMovementBehavior>([=](EntityMovementBehavior* entityMovementBehavior)
	{
		entityMovementBehavior->setMoveAcceleration(EntityRunBehavior::RunAcceleration);
	});
}

void EntityRunBehavior::onDisable()
{
	super::onDisable();
}
