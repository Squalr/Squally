#include "KingGroggBehaviorGroup.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"

#include "Engine/Maps/GameObject.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Enemies/Overworld/EndianForest/KingGrogg/GroggOutOfCombatAttackBehavior.h"

using namespace cocos2d;

const std::string KingGroggBehaviorGroup::MapKey = "king-grogg";

KingGroggBehaviorGroup* KingGroggBehaviorGroup::create(GameObject* owner)
{
	KingGroggBehaviorGroup* instance = new KingGroggBehaviorGroup(owner);

	instance->autorelease();

	return instance;
}

KingGroggBehaviorGroup::KingGroggBehaviorGroup(GameObject* owner) : super(owner, {
	GroggOutOfCombatAttackBehavior::create(owner),
	})
{
}

KingGroggBehaviorGroup::~KingGroggBehaviorGroup()
{
}

void KingGroggBehaviorGroup::onLoad()
{
}
