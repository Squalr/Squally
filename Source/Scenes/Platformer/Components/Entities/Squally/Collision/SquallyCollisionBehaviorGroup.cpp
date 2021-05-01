#include "SquallyCollisionBehaviorGroup.h"

#include "Engine/Maps/GameObject.h"
#include "Scenes/Platformer/Components/Entities/Squally/Collision/SquallyCollisionBehavior.h"
#include "Scenes/Platformer/Components/Entities/Squally/Collision/SquallyWeaponCollisionBehavior.h"

using namespace cocos2d;

const std::string SquallyCollisionBehaviorGroup::MapKey = "squally-collision-group";

SquallyCollisionBehaviorGroup* SquallyCollisionBehaviorGroup::create(GameObject* owner)
{
	SquallyCollisionBehaviorGroup* instance = new SquallyCollisionBehaviorGroup(owner);

	instance->autorelease();

	return instance;
}

SquallyCollisionBehaviorGroup::SquallyCollisionBehaviorGroup(GameObject* owner) : super(owner, {
	SquallyCollisionBehavior::create(owner),
	SquallyWeaponCollisionBehavior::create(owner),
	})
{
}

SquallyCollisionBehaviorGroup::~SquallyCollisionBehaviorGroup()
{
}

void SquallyCollisionBehaviorGroup::onLoad()
{
}
