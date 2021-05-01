#include "EntityMountBehavior.h"

#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"
#include "cocos/base/CCValue.h"

#include "Engine/Utils/GameUtils.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Objects/Platformer/Interactables/Mounts/MountBase.h"
#include "Scenes/Platformer/Components/Entities/Movement/EntityMovementBehavior.h"
#include "Scenes/Platformer/State/StateKeys.h"

using namespace cocos2d;

const std::string EntityMountBehavior::MapKey = "mount";

EntityMountBehavior* EntityMountBehavior::create(GameObject* owner)
{
	EntityMountBehavior* instance = new EntityMountBehavior(owner);

	instance->autorelease();

	return instance;
}

EntityMountBehavior::EntityMountBehavior(GameObject* owner) : super(owner)
{
	this->entity = dynamic_cast<PlatformerEntity*>(owner);
	this->mountTarget = nullptr;
	this->originalParent = nullptr;

	if (this->entity == nullptr)
	{
		this->invalidate();
	}
}

EntityMountBehavior::~EntityMountBehavior()
{
}

void EntityMountBehavior::onLoad()
{
}

bool EntityMountBehavior::mount(MountBase* mountTarget)
{
	if (this->entity == nullptr || this->mountTarget != nullptr)
	{
		return false;
	}

	this->originalParent = this->entity->getParent();
	this->mountTarget = mountTarget;

	GameUtils::changeParent(this->entity, this->mountTarget->getReparentNode(), false);
	
	this->entity->setState(StateKeys::MountHijacked, Value(true));

	return true;
}

bool EntityMountBehavior::dismount()
{
	if (this->entity == nullptr || this->mountTarget == nullptr)
	{
		return false;
	}

	this->mountTarget = nullptr;

	GameUtils::changeParent(this->entity, this->originalParent, true);
	this->entity->setState(StateKeys::MountHijacked, Value(false));

	return true;
}

void EntityMountBehavior::onDisable()
{
	super::onDisable();
}
