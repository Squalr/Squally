#include "SquallyBehaviors.h"

#include "Engine/Maps/GameObject.h"
#include "Scenes/Platformer/AttachedBehaviors/Squally/SquallyCollisionBehaviors.h"

using namespace cocos2d;

const std::string SquallyBehaviors::MapKeyAttachedBehavior = "squally";

SquallyBehaviors* SquallyBehaviors::create(GameObject* owner, std::string attachedBehaviorArgs)
{
	SquallyBehaviors* instance = new SquallyBehaviors(owner, attachedBehaviorArgs);

	instance->autorelease();

	return instance;
}

SquallyBehaviors::SquallyBehaviors(GameObject* owner, std::string attachedBehaviorArgs) : super(owner, attachedBehaviorArgs, {
	SquallyCollisionBehaviors::create(owner, attachedBehaviorArgs),
	})
{
}

SquallyBehaviors::~SquallyBehaviors()
{
}

void SquallyBehaviors::onLoad()
{
}
