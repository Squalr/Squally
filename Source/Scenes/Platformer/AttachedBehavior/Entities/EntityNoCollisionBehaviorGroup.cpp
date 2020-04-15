#include "EntityNoCollisionBehaviorGroup.h"

#include "Engine/Maps/GameObject.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Cinematic/EntityCinematicHijackBehavior.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Collision/EntityCollisionBehaviorGroup.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Developer/EntityDeveloperBehavior.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Dialogue/EntityDialogueBehavior.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Items/EntityInventoryBehavior.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Movement/EntityMovementBehavior.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Stats/EntityStatsBehaviorGroup.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Visual/EntityQuestVisualBehavior.h"

using namespace cocos2d;

const std::string EntityNoCollisionBehaviorGroup::MapKey = "entity-no-collision";

EntityNoCollisionBehaviorGroup* EntityNoCollisionBehaviorGroup::create(GameObject* owner)
{
	EntityNoCollisionBehaviorGroup* instance = new EntityNoCollisionBehaviorGroup(owner);

	instance->autorelease();

	return instance;
}

EntityNoCollisionBehaviorGroup::EntityNoCollisionBehaviorGroup(GameObject* owner) : super(owner, {
	EntityCinematicHijackBehavior::create(owner),
	EntityDeveloperBehavior::create(owner),
	EntityDialogueBehavior::create(owner),
	EntityInventoryBehavior::create(owner),
	EntityStatsBehaviorGroup::create(owner),
	EntityMovementBehavior::create(owner),
	EntityQuestVisualBehavior::create(owner),
	})
{
}

EntityNoCollisionBehaviorGroup::~EntityNoCollisionBehaviorGroup()
{
}

void EntityNoCollisionBehaviorGroup::onLoad()
{
}
