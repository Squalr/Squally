#include "SquallyAttackBehavior.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Input/ClickableNode.h"
#include "Entities/Platformer/PlatformerEnemy.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Entities/Platformer/PlatformerFriendly.h"
#include "Events/CombatEvents.h"
#include "Scenes/Platformer/Level/Combat/Attacks/Punch.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Combat/EntityAttackBehavior.h"

#include "Resources/UIResources.h"

using namespace cocos2d;
	
const std::string SquallyAttackBehavior::MapKeyAttachedBehavior = "entity-attacks";

SquallyAttackBehavior* SquallyAttackBehavior::create(GameObject* owner)
{
	SquallyAttackBehavior* instance = new SquallyAttackBehavior(owner);

	instance->autorelease();

	return instance;
}

SquallyAttackBehavior::SquallyAttackBehavior(GameObject* owner) : super(owner)
{
	this->entity = dynamic_cast<PlatformerEntity*>(owner);

	if (this->entity == nullptr)
	{
		this->invalidate();
	}
}

SquallyAttackBehavior::~SquallyAttackBehavior()
{
}

void SquallyAttackBehavior::initializePositions()
{
}

void SquallyAttackBehavior::onLoad()
{
	EntityAttackBehavior* attackBehavior = this->entity->getAttachedBehavior<EntityAttackBehavior>();
	
	if (attackBehavior != nullptr)
	{
		attackBehavior->registerAttack(Punch::create(0.4f, 0.5f));
	}
}
