#include "EntityBehaviorGroup.h"

#include "Engine/Maps/GameObject.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Combat/EntityProjectileTargetBehavior.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Cinematic/EntityCinematicHijackBehavior.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Collision/EntityCollisionBehaviorGroup.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Developer/EntityDeveloperBehavior.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Dialogue/EntityDialogueBehavior.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Inventory/EntityInventoryBehavior.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Movement/EntityMovementBehavior.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Stats/EntityStatsBehaviorGroup.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Visual/EntityQuestVisualBehavior.h"

using namespace cocos2d;

const std::string EntityBehaviorGroup::MapKey = "entity";

EntityBehaviorGroup* EntityBehaviorGroup::create(GameObject* owner)
{
	EntityBehaviorGroup* instance = new EntityBehaviorGroup(owner);

	instance->autorelease();

	return instance;
}

EntityBehaviorGroup::EntityBehaviorGroup(GameObject* owner) : super(owner, {
	EntityCinematicHijackBehavior::create(owner),
	EntityCollisionBehaviorGroup::create(owner),
	EntityDeveloperBehavior::create(owner),
	EntityDialogueBehavior::create(owner),
	EntityProjectileTargetBehavior::create(owner),
	EntityStatsBehaviorGroup::create(owner),
	EntityMovementBehavior::create(owner),
	EntityQuestVisualBehavior::create(owner),
	})
{
}

EntityBehaviorGroup::~EntityBehaviorGroup()
{
}

void EntityBehaviorGroup::onLoad()
{
}
