#include "SkeletalNecromancerCombatBehavior.h"

#include "Engine/Inventory/Inventory.h"
#include "Engine/Inventory/Item.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Inventory/EntityInventoryBehavior.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Combat/EntityAttackBehavior.h"
#include "Scenes/Platformer/Level/Combat/Attacks/Buffs/Strength/CastStrength.h"
#include "Scenes/Platformer/Level/Combat/Attacks/BaseAttacks/BasicSlash.h"

#include "Resources/UIResources.h"

using namespace cocos2d;
	
const std::string SkeletalNecromancerCombatBehavior::MapKey = "skeletal-necromancer-combat";

SkeletalNecromancerCombatBehavior* SkeletalNecromancerCombatBehavior::create(GameObject* owner)
{
	SkeletalNecromancerCombatBehavior* instance = new SkeletalNecromancerCombatBehavior(owner);

	instance->autorelease();

	return instance;
}

SkeletalNecromancerCombatBehavior::SkeletalNecromancerCombatBehavior(GameObject* owner) : super(owner)
{
	this->entity = dynamic_cast<PlatformerEntity*>(owner);

	if (this->entity == nullptr)
	{
		this->invalidate();
	}
	
	this->setTimelineSpeedBase(1.25f);
}

SkeletalNecromancerCombatBehavior::~SkeletalNecromancerCombatBehavior()
{
}

void SkeletalNecromancerCombatBehavior::initializePositions()
{
}

void SkeletalNecromancerCombatBehavior::onLoad()
{
	super::onLoad();
	
	this->entity->watchForAttachedBehavior<EntityAttackBehavior>([=](EntityAttackBehavior* attackBehavior)
	{
		attackBehavior->registerAttack(CastStrength::create(0.7f, EntityAttackBehavior::DefaultRecoverSpeed, PlatformerAttack::Priority::Guaranteed));
		attackBehavior->registerAttack(BasicSlash::create(3, 5, 0.7f, EntityAttackBehavior::DefaultRecoverSpeed, PlatformerAttack::Priority::Common));
	});
	
	this->entity->watchForAttachedBehavior<EntityInventoryBehavior>([=](EntityInventoryBehavior* entityInventoryBehavior)
	{
		Inventory* inventory = entityInventoryBehavior->getInventory();

		if (inventory != nullptr)
		{
		}
	});
}
