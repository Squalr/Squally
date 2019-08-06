#include "NpcBehaviors.h"

#include "Engine/Maps/GameObject.h"
#include "Scenes/Platformer/AttachedBehaviors/Npcs/NpcCollisionBehaviors.h"

using namespace cocos2d;

const std::string NpcBehaviors::MapKeyAttachedBehavior = "npc";

NpcBehaviors* NpcBehaviors::create(GameObject* owner, std::string attachedBehaviorArgs)
{
	NpcBehaviors* instance = new NpcBehaviors(owner, attachedBehaviorArgs);

	instance->autorelease();

	return instance;
}

NpcBehaviors::NpcBehaviors(GameObject* owner, std::string attachedBehaviorArgs) : super(owner, attachedBehaviorArgs, {
	NpcCollisionBehaviors::create(owner, attachedBehaviorArgs),
	})
{
}

NpcBehaviors::~NpcBehaviors()
{
}

void NpcBehaviors::onLoad()
{
}
