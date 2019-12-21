#include "ScrappyCombatBehaviorGroup.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"

#include "Engine/Maps/GameObject.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Dialogue/EntityDialogueBehavior.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Helpers/Scrappy/Combat/ScrappyHackableCueBehavior.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Helpers/Scrappy/ScrappyMovementBehavior.h"

using namespace cocos2d;

const std::string ScrappyCombatBehaviorGroup::MapKeyAttachedBehavior = "scrappy-combat";

ScrappyCombatBehaviorGroup* ScrappyCombatBehaviorGroup::create(GameObject* owner)
{
	ScrappyCombatBehaviorGroup* instance = new ScrappyCombatBehaviorGroup(owner);

	instance->autorelease();

	return instance;
}

ScrappyCombatBehaviorGroup::ScrappyCombatBehaviorGroup(GameObject* owner) : super(owner, {
	EntityDialogueBehavior::create(owner),
	ScrappyMovementBehavior::create(owner),
	ScrappyHackableCueBehavior::create(owner),
	})
{
}

ScrappyCombatBehaviorGroup::~ScrappyCombatBehaviorGroup()
{
}

void ScrappyCombatBehaviorGroup::onLoad()
{
}
