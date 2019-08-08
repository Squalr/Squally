#include "NpcBehaviorGroup.h"

#include "Engine/Maps/GameObject.h"
#include "Scenes/Platformer/AttachedBehaviors/Entities/EntityBehaviorGroup.h"
#include "Scenes/Platformer/AttachedBehaviors/Npcs/NpcCollisionBehaviors.h"

using namespace cocos2d;

const std::string NpcBehaviorGroup::MapKeyAttachedBehavior = "npc";

NpcBehaviorGroup* NpcBehaviorGroup::create(GameObject* owner, std::string attachedBehaviorArgs)
{
	NpcBehaviorGroup* instance = new NpcBehaviorGroup(owner, attachedBehaviorArgs);

	instance->autorelease();

	return instance;
}

NpcBehaviorGroup::NpcBehaviorGroup(GameObject* owner, std::string attachedBehaviorArgs) : super(owner, attachedBehaviorArgs, {
	NpcCollisionBehaviors::create(owner, attachedBehaviorArgs),
	EntityBehaviorGroup::create(owner, attachedBehaviorArgs),
	})
{
}

NpcBehaviorGroup::~NpcBehaviorGroup()
{
}

void NpcBehaviorGroup::onLoad()
{
}
