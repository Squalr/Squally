#include "EntityBehaviorGroup.h"

#include "Engine/Maps/GameObject.h"
#include "Scenes/Platformer/Components/Entities/Combat/EntityProjectileTargetBehavior.h"
#include "Scenes/Platformer/Components/Entities/Cinematic/EntityCinematicHijackBehavior.h"
#include "Scenes/Platformer/Components/Entities/Collision/EntityCollisionBehaviorGroup.h"
#include "Scenes/Platformer/Components/Entities/Developer/EntityDeveloperBehavior.h"
#include "Scenes/Platformer/Components/Entities/Dialogue/EntityDialogueBehavior.h"
#include "Scenes/Platformer/Components/Entities/Inventory/EntityInventoryBehavior.h"
#include "Scenes/Platformer/Components/Entities/Movement/EntityMountBehavior.h"
#include "Scenes/Platformer/Components/Entities/Movement/EntityMovementBehavior.h"
#include "Scenes/Platformer/Components/Entities/Stats/EntityStatsBehaviorGroup.h"
#include "Scenes/Platformer/Components/Entities/Visual/EntityQuestVisualBehavior.h"

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
	EntityMountBehavior::create(owner),
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
