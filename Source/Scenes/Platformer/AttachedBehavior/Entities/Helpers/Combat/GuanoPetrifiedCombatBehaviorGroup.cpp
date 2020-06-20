#include "GuanoPetrifiedCombatBehaviorGroup.h"

#include "cocos/base/CCValue.h"

#include "Engine/Maps/GameObject.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Combat/EntityBuffBehavior.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Helpers/Combat/GuanoAttackBehavior.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Helpers/Guano/GuanoEqBehavior.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Helpers/Guano/GuanoHealthBehavior.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Helpers/Guano/GuanoManaBehavior.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Helpers/Inventory/HelperInventoryRedirectBehavior.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Inventory/EntityInventoryBehavior.h"
#include "Scenes/Platformer/Level/Combat/Attacks/Buffs/GodMode/GodMode.h"
#include "Scenes/Platformer/Level/Combat/Attacks/Buffs/Pacifist/Pacifist.h"
#include "Scenes/Platformer/State/StateKeys.h"

using namespace cocos2d;

const std::string GuanoPetrifiedCombatBehaviorGroup::MapKey = "guano-petrified-combat";

GuanoPetrifiedCombatBehaviorGroup* GuanoPetrifiedCombatBehaviorGroup::create(GameObject* owner)
{
	GuanoPetrifiedCombatBehaviorGroup* instance = new GuanoPetrifiedCombatBehaviorGroup(owner);

	instance->autorelease();

	return instance;
}

GuanoPetrifiedCombatBehaviorGroup::GuanoPetrifiedCombatBehaviorGroup(GameObject* owner) : super(owner, {
	EntityInventoryBehavior::create(owner),
	HelperInventoryRedirectBehavior::create(owner),
	GuanoAttackBehavior::create(owner),
	GuanoEqBehavior::create(owner),
	GuanoHealthBehavior::create(owner),
	GuanoManaBehavior::create(owner),
	})
{
}

GuanoPetrifiedCombatBehaviorGroup::~GuanoPetrifiedCombatBehaviorGroup()
{
}

void GuanoPetrifiedCombatBehaviorGroup::onLoad()
{
	super::onLoad();

	this->entity->watchForAttachedBehavior<EntityBuffBehavior>([&](EntityBuffBehavior* entityBuffBehavior)
	{
		entityBuffBehavior->applyBuff(GodMode::create(this->entity, this->entity));
		entityBuffBehavior->applyBuff(Pacifist::create(this->entity, this->entity));
	});

	this->entity->listenForStateWrite(StateKeys::Health, [=](Value value)
	{
		this->entity->setState(StateKeys::Health, this->entity->getRuntimeStateOrDefault(StateKeys::MaxHealth, Value(0)), false);
	});
}

void GuanoPetrifiedCombatBehaviorGroup::onDisable()
{
	super::onDisable();
}
