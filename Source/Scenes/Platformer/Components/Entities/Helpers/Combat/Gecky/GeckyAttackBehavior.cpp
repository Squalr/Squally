#include "GeckyAttackBehavior.h"

#include "Engine/Inventory/Inventory.h"
#include "Engine/Inventory/Item.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Scenes/Platformer/Components/Entities/Inventory/EntityInventoryBehavior.h"
#include "Scenes/Platformer/Components/Entities/Combat/EntityAttackBehavior.h"
#include "Scenes/Platformer/Level/Combat/Attacks/BaseAttacks/BasicSlashAxe.h"

#include "Resources/UIResources.h"

using namespace cocos2d;
	
const std::string GeckyAttackBehavior::MapKey = "gecky-attack";

GeckyAttackBehavior* GeckyAttackBehavior::create(GameObject* owner)
{
	GeckyAttackBehavior* instance = new GeckyAttackBehavior(owner);

	instance->autorelease();

	return instance;
}

GeckyAttackBehavior::GeckyAttackBehavior(GameObject* owner) : super(owner)
{
	this->entity = dynamic_cast<PlatformerEntity*>(owner);

	if (this->entity == nullptr)
	{
		this->invalidate();
	}
}

GeckyAttackBehavior::~GeckyAttackBehavior()
{
}

void GeckyAttackBehavior::initializePositions()
{
}

void GeckyAttackBehavior::onLoad()
{
	this->entity->watchForComponent<EntityAttackBehavior>([=](EntityAttackBehavior* attackBehavior)
	{
		std::tuple<int, int> attackRange = attackBehavior->computeAttackRange();
		int minAttack = std::get<0>(attackRange);
		int maxAttack = std::get<1>(attackRange);

		attackBehavior->registerAttack(BasicSlashAxe::create(minAttack, maxAttack, 0.7f, EntityAttackBehavior::DefaultRecoverSpeed, PlatformerAttack::Priority::Common));
	});
}

void GeckyAttackBehavior::onDisable()
{
	super::onDisable();
}
