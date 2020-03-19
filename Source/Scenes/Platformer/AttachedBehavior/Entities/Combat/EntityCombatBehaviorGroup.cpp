#include "EntityCombatBehaviorGroup.h"

#include "Engine/Maps/GameObject.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Collision/EntityCollisionBehaviorGroup.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Combat/EntityAttackBehavior.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Combat/EntityBuffBehavior.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Combat/EntityDropTableBehavior.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Combat/EntityProjectileTargetBehavior.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Combat/EntitySelectionOverlayBehavior.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Combat/EntityTextOverlayBehavior.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Developer/EntityDeveloperBehavior.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Dialogue/EntityDialogueBehavior.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/EntitySelectionBehavior.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Items/EntityInventoryBehavior.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Stats/EntityStatsBehaviorGroup.h"

using namespace cocos2d;

const std::string EntityCombatBehaviorGroup::MapKey = "entity-combat-group";

EntityCombatBehaviorGroup* EntityCombatBehaviorGroup::create(GameObject* owner)
{
	EntityCombatBehaviorGroup* instance = new EntityCombatBehaviorGroup(owner);

	instance->autorelease();

	return instance;
}

EntityCombatBehaviorGroup::EntityCombatBehaviorGroup(GameObject* owner) : super(owner, {
	EntityAttackBehavior::create(owner),
	EntityBuffBehavior::create(owner),
	EntityDropTableBehavior::create(owner),
	EntityProjectileTargetBehavior::create(owner),
	EntitySelectionBehavior::create(owner),
	EntityDialogueBehavior::create(owner),
	EntityDeveloperBehavior::create(owner),
	EntityStatsBehaviorGroup::create(owner),
	EntityInventoryBehavior::create(owner),
	EntitySelectionOverlayBehavior::create(owner),
	EntityTextOverlayBehavior::create(owner),
	})
{
}

EntityCombatBehaviorGroup::~EntityCombatBehaviorGroup()
{
}

void EntityCombatBehaviorGroup::onLoad()
{
}
