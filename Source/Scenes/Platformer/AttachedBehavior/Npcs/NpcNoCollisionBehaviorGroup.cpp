#include "NpcNoCollisionBehaviorGroup.h"

#include "Engine/Maps/GameObject.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/EntityNoCollisionBehaviorGroup.h"
#include "Scenes/Platformer/AttachedBehavior/Npcs/NpcCollisionBehavior.h"

using namespace cocos2d;

const std::string NpcNoCollisionBehaviorGroup::MapKeyAttachedBehavior = "npc-no-collision";

NpcNoCollisionBehaviorGroup* NpcNoCollisionBehaviorGroup::create(GameObject* owner)
{
	NpcNoCollisionBehaviorGroup* instance = new NpcNoCollisionBehaviorGroup(owner);

	instance->autorelease();

	return instance;
}

NpcNoCollisionBehaviorGroup::NpcNoCollisionBehaviorGroup(GameObject* owner) : super(owner, {
	EntityNoCollisionBehaviorGroup::create(owner),
	})
{
}

NpcNoCollisionBehaviorGroup::~NpcNoCollisionBehaviorGroup()
{
}

void NpcNoCollisionBehaviorGroup::onLoad()
{
}
