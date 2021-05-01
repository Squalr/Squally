#include "OrcBomberBehaviorGroup.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"

#include "Engine/Maps/GameObject.h"
#include "Scenes/Platformer/Components/Entities/Enemies/Overworld/EndianForest/OrcBomber/OrcBomberOutOfCombatAttackBehavior.h"

using namespace cocos2d;

const std::string OrcBomberBehaviorGroup::MapKey = "orc-bomber";

OrcBomberBehaviorGroup* OrcBomberBehaviorGroup::create(GameObject* owner)
{
	OrcBomberBehaviorGroup* instance = new OrcBomberBehaviorGroup(owner);

	instance->autorelease();

	return instance;
}

OrcBomberBehaviorGroup::OrcBomberBehaviorGroup(GameObject* owner) : super(owner, {
	OrcBomberOutOfCombatAttackBehavior::create(owner),
	})
{
}

OrcBomberBehaviorGroup::~OrcBomberBehaviorGroup()
{
}

void OrcBomberBehaviorGroup::onLoad()
{
}
