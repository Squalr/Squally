#include "MeleeSwingOutOfCombatAttackBehavior.h"

#include "cocos/base/CCValue.h"

#include "Engine/Animations/SmartAnimationSequenceNode.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/Utils/GameUtils.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Events/PlatformerEvents.h"
#include "Scenes/Platformer/Components/Entities/Enemies/Combat/AgroBehavior.h"
#include "Scenes/Platformer/Level/Physics/PlatformerPhysicsTypes.h"
#include "Scenes/Platformer/State/StateKeys.h"

#include "Resources/FXResources.h"
#include "Resources/SoundResources.h"

using namespace cocos2d;

const std::string MeleeSwingOutOfCombatAttackBehavior::MapKey = "melee";

MeleeSwingOutOfCombatAttackBehavior* MeleeSwingOutOfCombatAttackBehavior::create(GameObject* owner)
{
	MeleeSwingOutOfCombatAttackBehavior* instance = new MeleeSwingOutOfCombatAttackBehavior(owner);

	instance->autorelease();

	return instance;
}

MeleeSwingOutOfCombatAttackBehavior::MeleeSwingOutOfCombatAttackBehavior(GameObject* owner) : super(owner)
{
	this->owner = dynamic_cast<PlatformerEntity*>(owner);

	if (this->owner == nullptr)
	{
		this->invalidate();
	}
}

MeleeSwingOutOfCombatAttackBehavior::~MeleeSwingOutOfCombatAttackBehavior()
{
}

void MeleeSwingOutOfCombatAttackBehavior::onLoad()
{
	super::onLoad();

	this->owner->watchForComponent<AgroBehavior>([=](AgroBehavior* agroBehavior)
	{
		this->agroBehavior = agroBehavior;
	});

	this->scheduleUpdate();
}

void MeleeSwingOutOfCombatAttackBehavior::onDisable()
{
	super::onDisable();
}

void MeleeSwingOutOfCombatAttackBehavior::update(float dt)
{
	super::update(dt);

	if (this->agroBehavior != nullptr
		&& this->owner != nullptr
		&& this->agroBehavior->hasAgro()
		&& this->agroBehavior->isInMeleeRange(420.0f)
		&& this->owner->getRuntimeStateOrDefaultBool(StateKeys::IsAlive, true))
	{
		this->attack();
	}
}

std::string MeleeSwingOutOfCombatAttackBehavior::getOutOfCombatAttackAnimation()
{
	return "Attack";
}

std::string MeleeSwingOutOfCombatAttackBehavior::getOutOfCombatAttackSound()
{
	return SoundResources::Platformer_Physical_Swings_SwingWeakBlade1;
}

float MeleeSwingOutOfCombatAttackBehavior::getOutOfCombatAttackOnset()
{
	return 0.25f;
}

float MeleeSwingOutOfCombatAttackBehavior::getOutOfCombatAttackSustain()
{
	return 2.25f;
}

float MeleeSwingOutOfCombatAttackBehavior::getOutOfCombatAttackCooldown()
{
	return 1.5f;
}
