#include "GoblinShamanBehaviorGroup.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"

#include "Engine/Maps/GameObject.h"
#include "Scenes/Platformer/Components/Entities/Enemies/Overworld/EndianForest/GoblinShaman/GoblinShamanOutOfCombatAttackBehavior.h"

using namespace cocos2d;

const std::string GoblinShamanBehaviorGroup::MapKey = "goblin-shaman";

GoblinShamanBehaviorGroup* GoblinShamanBehaviorGroup::create(GameObject* owner)
{
	GoblinShamanBehaviorGroup* instance = new GoblinShamanBehaviorGroup(owner);

	instance->autorelease();

	return instance;
}

GoblinShamanBehaviorGroup::GoblinShamanBehaviorGroup(GameObject* owner) : super(owner, {
	GoblinShamanOutOfCombatAttackBehavior::create(owner),
	})
{
}

GoblinShamanBehaviorGroup::~GoblinShamanBehaviorGroup()
{
}

void GoblinShamanBehaviorGroup::onLoad()
{
}
