#include "SkeletalPirateCombatBehavior.h"

#include "Engine/Inventory/Inventory.h"
#include "Engine/Inventory/Item.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Scenes/Platformer/Components/Entities/Inventory/EntityInventoryBehavior.h"
#include "Scenes/Platformer/Components/Entities/Combat/EntityAttackBehavior.h"
#include "Scenes/Platformer/Level/Combat/Attacks/Abilities/BasicSlash/BasicSlash.h"
#include "Scenes/Platformer/Level/Combat/Attacks/Debuffs/Blind/CastBlind.h"

#include "Resources/UIResources.h"

using namespace cocos2d;
	
const std::string SkeletalPirateCombatBehavior::MapKey = "skeletal-pirate-combat";

SkeletalPirateCombatBehavior* SkeletalPirateCombatBehavior::create(GameObject* owner)
{
	SkeletalPirateCombatBehavior* instance = new SkeletalPirateCombatBehavior(owner);

	instance->autorelease();

	return instance;
}

SkeletalPirateCombatBehavior::SkeletalPirateCombatBehavior(GameObject* owner) : super(owner)
{
	this->entity = dynamic_cast<PlatformerEntity*>(owner);

	if (this->entity == nullptr)
	{
		this->invalidate();
	}
	
	this->setTimelineSpeedBase(1.25f);
}

SkeletalPirateCombatBehavior::~SkeletalPirateCombatBehavior()
{
}

void SkeletalPirateCombatBehavior::initializePositions()
{
}

void SkeletalPirateCombatBehavior::onLoad()
{
	super::onLoad();
	
	this->entity->watchForComponent<EntityAttackBehavior>([=](EntityAttackBehavior* attackBehavior)
	{
		attackBehavior->registerAttack(CastBlind::create(0.7f, EntityAttackBehavior::DefaultRecoverSpeed, PlatformerAttack::Priority::Guaranteed));
		attackBehavior->registerAttack(BasicSlash::create(6, 8, 0.7f, EntityAttackBehavior::DefaultRecoverSpeed, PlatformerAttack::Priority::Common));
	});
	
	this->entity->watchForComponent<EntityInventoryBehavior>([=](EntityInventoryBehavior* entityInventoryBehavior)
	{
		Inventory* inventory = entityInventoryBehavior->getInventory();

		if (inventory != nullptr)
		{
		}
	});
}
