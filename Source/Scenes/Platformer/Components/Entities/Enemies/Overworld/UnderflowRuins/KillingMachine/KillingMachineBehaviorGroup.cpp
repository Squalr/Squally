#include "KillingMachineBehaviorGroup.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"

#include "Engine/Maps/GameObject.h"
#include "Scenes/Platformer/Components/Entities/Enemies/Overworld/UnderflowRuins/KillingMachine/KillingMachineHealthBehavior.h"
#include "Scenes/Platformer/Components/Entities/Enemies/Overworld/UnderflowRuins/KillingMachine/KillingMachineDamageBehavior.h"

using namespace cocos2d;

const std::string KillingMachineBehaviorGroup::MapKey = "killing-machine";

KillingMachineBehaviorGroup* KillingMachineBehaviorGroup::create(GameObject* owner)
{
	KillingMachineBehaviorGroup* instance = new KillingMachineBehaviorGroup(owner);

	instance->autorelease();

	return instance;
}

KillingMachineBehaviorGroup::KillingMachineBehaviorGroup(GameObject* owner) : super(owner, {
	KillingMachineHealthBehavior::create(owner),
	KillingMachineDamageBehavior::create(owner),
	})
{
}

KillingMachineBehaviorGroup::~KillingMachineBehaviorGroup()
{
}

void KillingMachineBehaviorGroup::onLoad()
{
}
