#include "SquallyStaticHelpBehavior.h"

#include "cocos/base/CCValue.h"
#include "cocos/math/CCGeometry.h"

#include "Engine/Physics/CollisionObject.h"
#include "Engine/Utils/GameUtils.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Collision/EntityCollisionBehaviorBase.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Inventory/EntityInventoryBehavior.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Stats/EntityHealthBehavior.h"
#include "Scenes/Platformer/Save/SaveKeys.h"
#include "Scenes/Platformer/State/StateKeys.h"

using namespace cocos2d;

const std::string SquallyStaticHelpBehavior::MapKey = "squally-static-help";

float* SquallyStaticHelpBehavior::PositionXPtr = nullptr;
float* SquallyStaticHelpBehavior::PositionYPtr = nullptr;
float* SquallyStaticHelpBehavior::PositionZPtr = nullptr;
float* SquallyStaticHelpBehavior::MovementXPtr = nullptr;
float* SquallyStaticHelpBehavior::MovementYPtr = nullptr;
float* SquallyStaticHelpBehavior::MovementZPtr = nullptr;
int* SquallyStaticHelpBehavior::HealthPtr = nullptr;
int* SquallyStaticHelpBehavior::ManaPtr = nullptr;
int* SquallyStaticHelpBehavior::EqPtr = nullptr;
int* SquallyStaticHelpBehavior::ExpPtr = nullptr;

SquallyStaticHelpBehavior* SquallyStaticHelpBehavior::create(GameObject* owner)
{
	SquallyStaticHelpBehavior* instance = new SquallyStaticHelpBehavior(owner);

	instance->autorelease();

	return instance;
}

SquallyStaticHelpBehavior::SquallyStaticHelpBehavior(GameObject* owner) : super(owner)
{
	this->squally = static_cast<Squally*>(owner);
}

SquallyStaticHelpBehavior::~SquallyStaticHelpBehavior()
{
}

void SquallyStaticHelpBehavior::onLoad()
{
	SquallyStaticHelpBehavior::PositionXPtr = &this->squally->getPositionPtr()->x;
	SquallyStaticHelpBehavior::PositionYPtr = &this->squally->getPositionPtr()->y;
	SquallyStaticHelpBehavior::PositionZPtr = this->squally->getPositionZPtr();

	SquallyStaticHelpBehavior::MovementXPtr = nullptr;
	SquallyStaticHelpBehavior::MovementYPtr = nullptr;
	SquallyStaticHelpBehavior::MovementZPtr = nullptr;

	SquallyStaticHelpBehavior::HealthPtr = (int*)&this->squally->getStateVariables()[StateKeys::Health];
	SquallyStaticHelpBehavior::ManaPtr = (int*)&this->squally->getStateVariables()[StateKeys::Mana];
	SquallyStaticHelpBehavior::EqPtr = (int*)&this->squally->getStateVariables()[StateKeys::Eq];
	SquallyStaticHelpBehavior::ExpPtr = (int*)&this->squally->getStateVariables()[StateKeys::EqExperience];

	this->squally->watchForAttachedBehavior<EntityCollisionBehaviorBase>([=](EntityCollisionBehaviorBase* collisionBehavior)
	{
		SquallyStaticHelpBehavior::PositionXPtr = &collisionBehavior->movementCollision->getPositionPtr()->x;
		SquallyStaticHelpBehavior::PositionYPtr = &collisionBehavior->movementCollision->getPositionPtr()->y;
		SquallyStaticHelpBehavior::PositionZPtr = collisionBehavior->movementCollision->getPositionZPtr();
	});
}

void SquallyStaticHelpBehavior::onDisable()
{
	super::onDisable();
}
