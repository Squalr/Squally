#include "SquallyAttackBehavior.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Input/ClickableNode.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Events/CombatEvents.h"
#include "Scenes/Platformer/Level/Combat/Attacks/Punch.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Combat/EntityAttackBehavior.h"

#include "Resources/UIResources.h"

using namespace cocos2d;
	
const std::string SquallyAttackBehavior::MapKeyAttachedBehavior = "squally-attacks";

SquallyAttackBehavior* SquallyAttackBehavior::create(GameObject* owner)
{
	SquallyAttackBehavior* instance = new SquallyAttackBehavior(owner);

	instance->autorelease();

	return instance;
}

SquallyAttackBehavior::SquallyAttackBehavior(GameObject* owner) : super(owner)
{
	this->squally = dynamic_cast<Squally*>(owner);

	if (this->squally == nullptr)
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
	this->squally->watchForAttachedBehavior<EntityAttackBehavior>([=](EntityAttackBehavior* attackBehavior)
	{
		attackBehavior->registerAttack(Punch::create(0.4f, 0.5f));
	});
}
