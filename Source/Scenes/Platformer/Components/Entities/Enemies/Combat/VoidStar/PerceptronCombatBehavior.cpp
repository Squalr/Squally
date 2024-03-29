#include "PerceptronCombatBehavior.h"

#include "Engine/Inventory/Inventory.h"
#include "Engine/Inventory/Item.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Scenes/Platformer/Components/Entities/Inventory/EntityInventoryBehavior.h"
#include "Scenes/Platformer/Components/Entities/Combat/EntityAttackBehavior.h"
#include "Scenes/Platformer/Level/Combat/Attacks/Buffs/MultiCast/CastStoneSkinHaste.h"
#include "Scenes/Platformer/Level/Combat/Attacks/Buffs/Strength/CastStrength.h"
#include "Scenes/Platformer/Level/Combat/Attacks/Abilities/BasicSlash/BasicSlash.h"
#include "Scenes/Platformer/Level/Combat/Attacks/Abilities/LavaAxe/CastLavaAxe.h"
#include "Scenes/Platformer/Level/Combat/Attacks/Debuffs/Daze/CastDaze.h"
#include "Scenes/Platformer/Level/Combat/Attacks/Debuffs/ManaDrain/CastManaDrain.h"

#include "Resources/UIResources.h"

using namespace cocos2d;
	
const std::string PerceptronCombatBehavior::MapKey = "perceptron-combat";

PerceptronCombatBehavior* PerceptronCombatBehavior::create(GameObject* owner)
{
	PerceptronCombatBehavior* instance = new PerceptronCombatBehavior(owner);

	instance->autorelease();

	return instance;
}

PerceptronCombatBehavior::PerceptronCombatBehavior(GameObject* owner) : super(owner)
{
	this->entity = dynamic_cast<PlatformerEntity*>(owner);

	if (this->entity == nullptr)
	{
		this->invalidate();
	}
	
	this->setTimelineSpeedBase(1.25f);
}

PerceptronCombatBehavior::~PerceptronCombatBehavior()
{
}

void PerceptronCombatBehavior::initializePositions()
{
}

void PerceptronCombatBehavior::onLoad()
{
	super::onLoad();
	
	this->entity->watchForComponent<EntityAttackBehavior>([=](EntityAttackBehavior* attackBehavior)
	{
		attackBehavior->registerAttack(CastStoneSkinHaste::create(0.7f, EntityAttackBehavior::DefaultRecoverSpeed, PlatformerAttack::Priority::Guaranteed));
		attackBehavior->registerAttack(CastManaDrain::create(0.7f, EntityAttackBehavior::DefaultRecoverSpeed, PlatformerAttack::Priority::Common));
		attackBehavior->registerAttack(CastDaze::create(0.7f, EntityAttackBehavior::DefaultRecoverSpeed, PlatformerAttack::Priority::Common));
		attackBehavior->registerAttack(CastLavaAxe::create(0.7f, EntityAttackBehavior::DefaultRecoverSpeed, PlatformerAttack::Priority::Common));
		attackBehavior->registerAttack(BasicSlash::create(19, 20, 0.7f, EntityAttackBehavior::DefaultRecoverSpeed, PlatformerAttack::Priority::IfNecessary));
	});
	
	this->entity->watchForComponent<EntityInventoryBehavior>([=](EntityInventoryBehavior* entityInventoryBehavior)
	{
		Inventory* inventory = entityInventoryBehavior->getInventory();

		if (inventory != nullptr)
		{
		}
	});
}
