#include "NpcBehaviorGroup.h"

#include "Engine/Maps/GameObject.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/EntityBehaviorGroup.h"
#include "Scenes/Platformer/AttachedBehavior/Npcs/NpcCollisionBehavior.h"

using namespace cocos2d;

const std::string NpcBehaviorGroup::MapKeyAttachedBehavior = "npc";

NpcBehaviorGroup* NpcBehaviorGroup::create(GameObject* owner)
{
	NpcBehaviorGroup* instance = new NpcBehaviorGroup(owner);

	instance->autorelease();

	return instance;
}

NpcBehaviorGroup::NpcBehaviorGroup(GameObject* owner) : super(owner, {
	NpcCollisionBehavior::create(owner),
	EntityBehaviorGroup::create(owner),
	})
{
}

NpcBehaviorGroup::~NpcBehaviorGroup()
{
}

void NpcBehaviorGroup::onLoad()
{
}
