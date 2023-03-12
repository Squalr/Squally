#include "SkeletalNecromancerCombatBehavior.h"

#include "Engine/Inventory/Inventory.h"
#include "Engine/Inventory/Item.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Scenes/Platformer/Components/Entities/Combat/EntityBuffBehavior.h"
#include "Scenes/Platformer/Components/Entities/Inventory/EntityInventoryBehavior.h"
#include "Scenes/Platformer/Components/Entities/Combat/EntityAttackBehavior.h"
#include "Scenes/Platformer/Level/Combat/Attacks/Abilities/BasicSlash/BasicSlash.h"
#include "Scenes/Platformer/Level/Combat/Attacks/Buffs/PactOfTheAncients/PactOfTheAncients.h"

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
	
	this->entity->watchForComponent<EntityAttackBehavior>([=](EntityAttackBehavior* attackBehavior)
	{
		attackBehavior->registerAttack(BasicSlash::create(5, 7, 0.7f, EntityAttackBehavior::DefaultRecoverSpeed, PlatformerAttack::Priority::IfNecessary));
	});
	
	this->entity->watchForComponent<EntityBuffBehavior>([&](EntityBuffBehavior* entityBuffBehavior)
	{
		entityBuffBehavior->applyBuff(PactOfTheAncients::create(this->entity, this->entity));
	});
	
	this->entity->watchForComponent<EntityInventoryBehavior>([=](EntityInventoryBehavior* entityInventoryBehavior)
	{
		Inventory* inventory = entityInventoryBehavior->getInventory();

		if (inventory != nullptr)
		{
		}
	});
}
