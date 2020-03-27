#include "DropTimeBomb.h"

#include "cocos/2d/CCActionInterval.h"

#include "Engine/Animations/SmartAnimationSequenceNode.h"
#include "Engine/Events/ObjectEvents.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/Sound/WorldSound.h"
#include "Engine/Utils/GameUtils.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Events/CombatEvents.h"
#include "Objects/Platformer/Projectiles/Combat/TimeBomb/TimeBomb.h"
#include "Objects/Platformer/Projectiles/Combat/ThrownObject/ThrownObject.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Combat/EntityProjectileTargetBehavior.h"
#include "Scenes/Platformer/Level/Combat/Physics/CombatCollisionType.h"

#include "Resources/FXResources.h"
#include "Resources/SoundResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

DropTimeBomb* DropTimeBomb::create(float attackDuration, float recoverDuration, Priority priority)
{
	DropTimeBomb* instance = new DropTimeBomb(attackDuration, recoverDuration, priority);

	instance->autorelease();

	return instance;
}

DropTimeBomb::DropTimeBomb(float attackDuration, float recoverDuration, Priority priority) : super(AttackType::Damage, UIResources::Menus_Icons_Clock, priority, 450, 500, 12, attackDuration, recoverDuration)
{
}

DropTimeBomb::~DropTimeBomb()
{
}

PlatformerAttack* DropTimeBomb::cloneInternal()
{
	return DropTimeBomb::create(this->getAttackDuration(), this->getRecoverDuration(), this->priority);
}

LocalizedString* DropTimeBomb::getString()
{
	return Strings::Platformer_Combat_Attacks_Slash::create();
}

std::string DropTimeBomb::getAttackAnimation()
{
	return "DropTimeBomb";
}

void DropTimeBomb::performAttack(PlatformerEntity* owner, PlatformerEntity* target)
{
	super::performAttack(owner, target);

	TimeBomb* timeBomb = TimeBomb::create(owner, target);

	ObjectEvents::TriggerObjectSpawn(ObjectEvents::RequestObjectSpawnArgs(
		owner,
		timeBomb,
		ObjectEvents::SpawnMethod::Above,
		ObjectEvents::PositionMode::Discard,
		[&]()
		{
		},
		[&]()
		{
		}
	));

	timeBomb->runSpawnFX();
	timeBomb->setPosition3D(GameUtils::getWorldCoords3D(target) + Vec3((target->isFlippedX() ? -96.0f : 96.0f), 0.0f, 0.0f));
}

void DropTimeBomb::onCleanup()
{
}
