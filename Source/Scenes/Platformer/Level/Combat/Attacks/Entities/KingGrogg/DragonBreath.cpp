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
#include "Objects/Platformer/Combat/Projectiles/ThrownObject/Fireball.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Combat/EntityProjectileTargetBehavior.h"

#include "Resources/FXResources.h"
#include "Resources/SoundResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

DragonBreath* DragonBreath::create(float attackDuration, float recoverDuration, float priority)
{
	DragonBreath* instance = new DragonBreath(attackDuration, recoverDuration, priority);

	instance->autorelease();

	return instance;
}

DragonBreath::DragonBreath(float attackDuration, float recoverDuration, float priority) : super(AttackType::Damage, UIResources::Menus_Icons_FireBalls, priority, 7, 9, 12, attackDuration, recoverDuration)
{
}

DragonBreath::~DragonBreath()
{
}

PlatformerAttack* DragonBreath::cloneInternal()
{
	return DragonBreath::create(this->getAttackDuration(), this->getRecoverDuration(), this->priority);
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

	SmartAnimationSequenceNode* fireBreath = SmartAnimationSequenceNode::create();
	WorldSound* breathSound = WorldSound::create(SoundResources::Platformer_Combat_Attacks_Spells_Fireball2);
	Fireball* fireball = Fireball::create(owner, this);

	fireBreath->playAnimation(FXResources::FireBreath_FireBreath_0000, 0.05f, true);
	fireBreath->setFlippedX(owner->isFlippedX());
	fireBreath->addChild(breathSound);

	ObjectEvents::TriggerObjectSpawn(ObjectEvents::RequestObjectSpawnArgs(owner, fireball, ObjectEvents::SpawnMethod::Above, ObjectEvents::PositionMode::Discard));
	ObjectEvents::TriggerObjectSpawn(ObjectEvents::RequestObjectSpawnArgs(owner, fireBreath, ObjectEvents::SpawnMethod::Above, ObjectEvents::PositionMode::Discard));
	
	fireball->setPosition3D(GameUtils::getWorldCoords3D(owner) + Vec3((owner->isFlippedX() ? -96.0f : 96.0f), 96.0f, 0.0f));
	fireBreath->setPosition3D(GameUtils::getWorldCoords3D(fireball) + Vec3((owner->isFlippedX() ? -180.0f : 180.0f), 0.0f, 0.0f));

	breathSound->play();

	target->getAttachedBehavior<EntityProjectileTargetBehavior>([=](EntityProjectileTargetBehavior* behavior)
	{
		fireball->getProjectile()->launchTowardsTarget(behavior->getTarget(), Vec2::ZERO, 0.0f, Vec3(0.3f, 0.3f, 0.3f), Vec3(0.0f, -64.0f, 0.0f));
	});
}

void DragonBreath::onCleanup()
{
}
