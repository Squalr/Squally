#include "EntityCombatBehaviorGroup.h"

#include "Engine/Maps/GameObject.h"
#include "Scenes/Platformer/Components/Entities/Collision/EntityDisableMovementCollisionBehavior.h"
#include "Scenes/Platformer/Components/Entities/Combat/EntityAttackBehavior.h"
#include "Scenes/Platformer/Components/Entities/Combat/EntityBuffBehavior.h"
#include "Scenes/Platformer/Components/Entities/Combat/EntityDropTableBehavior.h"
#include "Scenes/Platformer/Components/Entities/Combat/EntityProjectileTargetBehavior.h"
#include "Scenes/Platformer/Components/Entities/Combat/EntitySelectionOverlayBehavior.h"
#include "Scenes/Platformer/Components/Entities/Combat/EntityTextOverlayBehavior.h"
#include "Scenes/Platformer/Components/Entities/Developer/EntityDeveloperBehavior.h"
#include "Scenes/Platformer/Components/Entities/Dialogue/EntityDialogueBehavior.h"
#include "Scenes/Platformer/Components/Entities/EntitySelectionBehavior.h"
#include "Scenes/Platformer/Components/Entities/Inventory/EntityInventoryBehavior.h"
#include "Scenes/Platformer/Components/Entities/Stats/EntityStatsBehaviorGroup.h"

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
	EntityDisableMovementCollisionBehavior::create(owner),
	EntitySelectionBehavior::create(owner),
	EntityDialogueBehavior::create(owner),
	EntityDeveloperBehavior::create(owner),
	EntityStatsBehaviorGroup::create(owner),
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
