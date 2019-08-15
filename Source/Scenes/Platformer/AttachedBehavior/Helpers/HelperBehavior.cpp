#include "HelperBehavior.h"

#include "cocos/base/CCValue.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Input/Input.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/Save/SaveManager.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Collision/EntityGroundCollisionBehavior.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Collision/EntityMovementCollisionBehavior.h"
#include "Scenes/Platformer/State/StateKeys.h"

#include "Resources/EntityResources.h"

using namespace cocos2d;

const std::string HelperBehavior::MapKeyAttachedBehavior = "entity-helper";

HelperBehavior* HelperBehavior::create(GameObject* owner)
{
	HelperBehavior* instance = new HelperBehavior(owner);

	instance->autorelease();

	return instance;
}

HelperBehavior::HelperBehavior(GameObject* owner) : super(owner)
{
	this->entity = dynamic_cast<PlatformerEntity*>(owner);

	if (this->entity == nullptr)
	{
		this->invalidate();
	}
}

HelperBehavior::~HelperBehavior()
{
}

void HelperBehavior::onLoad()
{
	this->scheduleUpdate();
}
