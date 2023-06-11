#include "GrimAttackBehavior.h"

#include "Engine/Inventory/Inventory.h"
#include "Engine/Inventory/Item.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Scenes/Platformer/Components/Entities/Inventory/EntityInventoryBehavior.h"
#include "Scenes/Platformer/Components/Entities/Combat/EntityAttackBehavior.h"
#include "Scenes/Platformer/Level/Combat/Attacks/Abilities/BasicSlashAxe/BasicSlashAxe.h"
#include "Scenes/Platformer/Level/Combat/Attacks/Abilities/LifeSteal/CastLifeSteal.h"
#include "Scenes/Platformer/Level/Combat/Buffs/Defend/CastDefend.h"

#include "Resources/UIResources.h"

using namespace cocos2d;
	
const std::string GrimAttackBehavior::MapKey = "grim-attack";

GrimAttackBehavior* GrimAttackBehavior::create(GameObject* owner)
{
	GrimAttackBehavior* instance = new GrimAttackBehavior(owner);

	instance->autorelease();

	return instance;
}

GrimAttackBehavior::GrimAttackBehavior(GameObject* owner) : super(owner)
{
	this->entity = dynamic_cast<PlatformerEntity*>(owner);

	if (this->entity == nullptr)
	{
		this->invalidate();
	}
}

GrimAttackBehavior::~GrimAttackBehavior()
{
}

void GrimAttackBehavior::initializePositions()
{
}

void GrimAttackBehavior::onLoad()
{
	this->entity->watchForComponent<EntityAttackBehavior>([=](EntityAttackBehavior* attackBehavior)
	{
		std::tuple<int, int> attackRange = attackBehavior->computeAttackRange();
		int minAttack = std::get<0>(attackRange);
		int maxAttack = std::get<1>(attackRange);

		attackBehavior->registerAttack(BasicSlashAxe::create(minAttack, maxAttack, 0.7f, EntityAttackBehavior::DefaultRecoverSpeed, PlatformerAttack::Priority::Common));
		attackBehavior->registerAttack(CastLifeSteal::create(minAttack, maxAttack, 0.7f, EntityAttackBehavior::DefaultRecoverSpeed, PlatformerAttack::Priority::Common));
		attackBehavior->registerDefensive(CastDefend::create(0.7f, EntityAttackBehavior::DefaultRecoverSpeed, PlatformerAttack::Priority::Common));
	});
}

void GrimAttackBehavior::onDisable()
{
	super::onDisable();
}
