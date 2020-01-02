#include "DragonBreath.h"

#include "cocos/2d/CCActionInterval.h"

#include "Engine/Animations/SmartAnimationSequenceNode.h"
#include "Engine/Events/ObjectEvents.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/Sound/WorldSound.h"
#include "Engine/Utils/GameUtils.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Events/CombatEvents.h"
#include "Objects/Platformer/Combat/Projectiles/ThrownObject/ThrownObject.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Combat/EntityProjectileTargetBehavior.h"

#include "Resources/FXResources.h"
#include "Resources/SoundResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

DragonBreath* DragonBreath::create(float attackDuration, float recoverDuration)
{
	DragonBreath* instance = new DragonBreath(attackDuration, recoverDuration);

	instance->autorelease();

	return instance;
}

DragonBreath::DragonBreath(float attackDuration, float recoverDuration) : super(AttackType::Damage, UIResources::Menus_Icons_FireBalls, 1.5f, 5, 7, 4, attackDuration, recoverDuration)
{
}

DragonBreath::~DragonBreath()
{
}

PlatformerAttack* DragonBreath::cloneInternal()
{
	return DragonBreath::create(this->getAttackDuration(), this->getRecoverDuration());
}

LocalizedString* DragonBreath::getString()
{
	return Strings::Platformer_Combat_Attacks_Slash::create();
}

std::string DragonBreath::getAttackAnimation()
{
	return "AttackDragon";
}

void DragonBreath::performAttack(PlatformerEntity* owner, PlatformerEntity* target)
{
	super::performAttack(owner, target);

	SmartAnimationSequenceNode* fireballAnim = SmartAnimationSequenceNode::create(FXResources::FireBall_FireBall_0000);
	SmartAnimationSequenceNode* fireBreath = SmartAnimationSequenceNode::create();
	ThrownObject* fireball = ThrownObject::create(owner, fireballAnim, Size(32.0f, 32.0f));
	WorldSound* breathSound = WorldSound::create(SoundResources::Platformer_Combat_Attacks_Spells_Fireball2);

	fireballAnim->playAnimationRepeat(FXResources::FireBall_FireBall_0000, 0.05f);
	fireBreath->playAnimation(FXResources::FireBreath_FireBreath_0000, 0.05f, true);
	fireBreath->setFlippedX(owner->isFlippedX());
	fireBreath->addChild(breathSound);

	ObjectEvents::TriggerObjectSpawn(ObjectEvents::RequestObjectSpawnArgs(owner, fireball, ObjectEvents::SpawnMethod::Above, ObjectEvents::PositionMode::Discard));
	ObjectEvents::TriggerObjectSpawn(ObjectEvents::RequestObjectSpawnArgs(owner, fireBreath, ObjectEvents::SpawnMethod::Above, ObjectEvents::PositionMode::Discard));
	
	fireball->setPosition3D(GameUtils::getWorldCoords3D(owner) + Vec3((owner->isFlippedX() ? -96.0f : 96.0f), 96.0f, 0.0f));
	fireBreath->setPosition3D(GameUtils::getWorldCoords3D(fireballAnim) + Vec3((owner->isFlippedX() ? -180.0f : 180.0f), 0.0f, 0.0f));

	breathSound->play();

	fireball->getCollision()->whenCollidesWith({ (int)CombatCollisionType::EntityEnemy, (int)CombatCollisionType::EntityFriendly }, [=](CollisionObject::CollisionData collisionData)
	{
		fireball->getCollision()->setPhysicsEnabled(false);
		fireball->setVisible(false);

		// Explosion animation
		SmartAnimationSequenceNode* explosionAnim = SmartAnimationSequenceNode::create(FXResources::Explosion_Explosion_0000);
		WorldSound* impactSound = WorldSound::create(SoundResources::Platformer_Combat_Attacks_Spells_FireHit1);
		
		ObjectEvents::TriggerObjectSpawn(ObjectEvents::RequestObjectSpawnArgs(owner, explosionAnim, ObjectEvents::SpawnMethod::Above, ObjectEvents::PositionMode::Discard));
		explosionAnim->playAnimation(FXResources::Explosion_Explosion_0000, 0.05f, true);
		explosionAnim->setPosition3D(GameUtils::getWorldCoords3D(fireball));
		explosionAnim->addChild(impactSound);

		impactSound->play();

		PlatformerEntity* entity = GameUtils::getFirstParentOfType<PlatformerEntity>(collisionData.other, true);

		if (entity != nullptr)
		{
			CombatEvents::TriggerDamageOrHealing(CombatEvents::DamageOrHealingArgs(owner, entity, this->getRandomDamage()));
		}

		return CollisionObject::CollisionResult::DoNothing;
	});

	target->getAttachedBehavior<EntityProjectileTargetBehavior>([=](EntityProjectileTargetBehavior* behavior)
	{
		fireball->launchTowardsTarget(behavior->getTarget(), Vec2::ZERO, 0.0f, Vec3(0.3f, 0.3f, 0.3f), Vec3(0.0f, -64.0f, 0.0f));
	});
}

void DragonBreath::onCleanup()
{
}
