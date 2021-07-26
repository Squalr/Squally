#include "TikiGolemCombatBehavior.h"

#include "Engine/Inventory/Inventory.h"
#include "Engine/Inventory/Item.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Scenes/Platformer/Components/Entities/Inventory/EntityInventoryBehavior.h"
#include "Scenes/Platformer/Components/Entities/Combat/EntityAttackBehavior.h"
#include "Scenes/Platformer/Level/Combat/Attacks/Abilities/BasicSlash/BasicSlash.h"
#include "Scenes/Platformer/Level/Combat/Attacks/Debuffs/CurseOfTheAncients/CastCurseOfTheAncients.h"

#include "Resources/UIResources.h"

using namespace cocos2d;
	
const std::string TikiGolemCombatBehavior::MapKey = "tiki-golem-combat";

TikiGolemCombatBehavior* TikiGolemCombatBehavior::create(GameObject* owner)
{
	TikiGolemCombatBehavior* instance = new TikiGolemCombatBehavior(owner);

	instance->autorelease();

	return instance;
}

TikiGolemCombatBehavior::TikiGolemCombatBehavior(GameObject* owner) : super(owner)
{
	this->entity = dynamic_cast<PlatformerEntity*>(owner);

	if (this->entity == nullptr)
	{
		this->invalidate();
	}
	
	this->setTimelineSpeedBase(1.55f);
}

TikiGolemCombatBehavior::~TikiGolemCombatBehavior()
{
}

void TikiGolemCombatBehavior::initializePositions()
{
}

void TikiGolemCombatBehavior::onLoad()
{
	super::onLoad();
	
	this->entity->watchForComponent<EntityAttackBehavior>([=](EntityAttackBehavior* attackBehavior)
	{
		attackBehavior->registerAttack(CastCurseOfTheAncients::create(0.7f, EntityAttackBehavior::DefaultRecoverSpeed, PlatformerAttack::Priority::Guaranteed));
		attackBehavior->registerAttack(BasicSlash::create(3, 5, 0.7f, EntityAttackBehavior::DefaultRecoverSpeed, PlatformerAttack::Priority::Common));
	});
	
	this->entity->watchForComponent<EntityInventoryBehavior>([=](EntityInventoryBehavior* entityInventoryBehavior)
	{
		Inventory* inventory = entityInventoryBehavior->getInventory();

		if (inventory != nullptr)
		{
		}
	});
}
